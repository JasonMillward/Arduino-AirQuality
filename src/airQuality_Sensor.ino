/**
 *  Arduino air quality sesnor array thing
 *
 *  Lots of sensors, all put together in a tiny box
 *
 */

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT22.h>
#include <Wire.h>
#include <SPI.h>
#include <stdlib.h>
#include <RTClib.h>


Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
DHT22 myDHT22(8);
RTC_DS1307 RTC;

char buf[128];

int dustPin       = 0;
int ledPower      = 2;
int delayTime     = 280;
int delayTime2    = 40;
int dustVal       = 0;

int sensorValue   = 0;

float ppm         = 0;
float offTime     = 9680;

float voltage     = 0;
float dustdensity = 0;
float ppmpercf    = 0;


void setup() {
  Serial.begin(9600);

  Wire.begin();
  RTC.begin();

  pinMode(ledPower, OUTPUT);

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");

    // Set the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  display.begin();
  display.setContrast(60);
}


void loop() {
  // Clear the screen and prepare it for text
  prepareDisplay();
  //progressBar();

  displayTitle();
  displayTemp();
  displayHumidity();
  readCOSensor();
  displayDustText();
  display.display();
  delay(2000);
}

void prepareDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);

}

void displayTitle() {
  display.setCursor(0,0);

  DateTime now = RTC.now();
  sprintf(buf,
          "%i:%i:%i",
          now.hour(),
          now.minute(),
          now.second()
  );

  display.println(buf);

  display.drawLine(0, 8, display.width(), 8, BLACK);
}

void displayTemp() {
  display.setCursor(0, 19);

  DHT22_ERROR_t errorCode;
  errorCode = myDHT22.readData();

  sprintf(buf,
          "Temp:  %hi.%01hi$",
          myDHT22.getTemperatureCInt() / 10,
          abs( myDHT22.getTemperatureCInt() % 10 )
  );
  display.println(buf);

}

void displayHumidity() {
  display.setCursor(0,11);

  DHT22_ERROR_t errorCode;
  errorCode = myDHT22.readData();

  sprintf(buf,
          "Humid: %i.%01i%%",
          myDHT22.getHumidityInt()/10, myDHT22.getHumidityInt()%10);

  display.println(buf);
}

void readCOSensor() {
  sensorValue = analogRead(2);
  Serial.println(sensorValue);
  delay(1000);
}

void displayDustText() {
  display.setCursor(0, 27);

  digitalWrite(ledPower,LOW );

  delayMicroseconds(delayTime );

  dustVal = analogRead(dustPin );
  ppm     = ppm+dustVal;

  delayMicroseconds(delayTime2 );

  digitalWrite(ledPower, HIGH );

  delayMicroseconds(offTime );

  voltage       = ppm / 1 * 0.0049;
  ppmpercf      = ( voltage - 0.0256 ) * 120000;
  dustdensity   = 0.17 * voltage - 0.1;
  ppm           = 0;

  if ( ppmpercf < 0 ) {
    ppmpercf = 0;
  }

  if ( ppmpercf < 75 ) {
    sprintf(buf,
            "Dust:  None"
    );
  } else if( ppmpercf > 75 && ppmpercf < 150 ) {
    sprintf(buf,
            "Dust:  V Low"
    );
  } else if( ppmpercf > 150 && ppmpercf < 300 ) {
    sprintf(buf,
            "Dust:  Low"
    );
  } else if( ppmpercf > 300 && ppmpercf < 1050 ) {
    sprintf(buf,
            "Dust:  Med"
    );
  } else if( ppmpercf > 1050 && ppmpercf < 3000   ) {
    sprintf(buf,
            "Dust:  High"
    );
  } else if ( ppmpercf < 3000 ) {
    sprintf(buf,
            "Dust:  V High"
    );
  } else {
    sprintf(buf,
            "Unknown %i",
            ppmpercf
    );
  }

  display.println( buf );

}

void progressBar() {
  // Add percent param later on
  display.drawLine(0, 46, display.width() / 3, 46, BLACK);
  display.drawRoundRect(0, 45, display.width(), 3, 1, BLACK);
}
