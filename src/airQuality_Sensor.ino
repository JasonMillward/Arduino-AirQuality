/**
 *  Arduino air quality sesnor array thing
 *
 *  Lots of sensors, all put together in a tiny box
 *
 */

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);


void setup() {
  display.begin();
  display.setContrast(60);
}


void loop() {
  // Clear the screen and prepare it for text
  prepareDisplay();
  //progressBar();

  displayTitle();
  displayTemp();

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
  display.println("Air Sensors");
  display.drawLine(0, 8, display.width(), 8, BLACK);
}

void displayTemp() {
  display.setCursor(0,11);
  display.println("Temp:  30*");
}

void progressBar() {
  // Add percent param later on
  display.drawLine(0, 46, display.width() / 3, 46, BLACK);
  display.drawRoundRect(0, 45, display.width(), 3, 1, BLACK);
}
