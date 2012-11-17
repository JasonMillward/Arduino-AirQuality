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
#include "<RTClib.h>"


Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
DHT22 myDHT22(8);
RTC_DS1307 RTC;

char buf[128];

void setup() {
  Wire.begin();
  RTC.begin();

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
  sprintf(buf, "%i:%i:%i",
                now.hour(),
                now.minute(),
                now.second()
  );

  display.println(buf);

  display.drawLine(0, 8, display.width(), 8, BLACK);
}

void displayTemp() {
  display.setCursor(0,11);

  sprintf(buf, "Temp:  %hi.%01hi$",
                myDHT22.getTemperatureCInt()/10, abs(myDHT22.getTemperatureCInt()%10));
  display.println(buf);

}

void displayHumidity() {
  display.setCursor(0,8);

  sprintf(buf, "Humid: %i.%01i%%",
                myDHT22.getHumidityInt()/10, myDHT22.getHumidityInt()%10);

  display.println(buf);
}

void progressBar() {
  // Add percent param later on
  display.drawLine(0, 46, display.width() / 3, 46, BLACK);
  display.drawRoundRect(0, 45, display.width(), 3, 1, BLACK);
}
