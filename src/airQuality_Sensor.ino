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

  display.clearDisplay();

  display.setTextSize(1);

  display.setTextColor(BLACK);

  display.setCursor(0,0);

  display.println("Test");

  display.display();

}