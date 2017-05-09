/* This minimal example shows how to get single-shot range
measurements from the VL6180X.

The range readings are in units of mm. */


#include <VL6180X.h>
 #include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
 #include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
float fl_average = 0;


VL6180X sensor;
unsigned long timer = 0;
int mm;
SSD1306  display(0x3c, D1, D2); 



void setup() 
{
  Wire.begin();
  
  display.init();
  display.setFont(ArialMT_Plain_24);
  //display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  sensor.init();
  sensor.configureDefault();
  //sensor.setScaling(2);
  sensor.setTimeout(500);
  timer = millis();
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void drawArrow(int xLoc) {
    display.drawVerticalLine(xLoc, 32, 16);
    display.drawVerticalLine(xLoc + 1, 42, 4);
    display.drawVerticalLine(xLoc + 2, 42, 2);
    display.drawVerticalLine(xLoc - 1, 42, 4);
    display.drawVerticalLine(xLoc - 2, 42, 2);
    
}

void loop() 
{ 
  mm = sensor.readRangeSingleMillimeters();
 if (millis() > timer + 100) {
    timer = millis();
    
  }
  if (millis() < timer) {timer = millis();}


  total = total - readings[readIndex];
  readings[readIndex] = mm;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  fl_average = average;
    display.clear();
    display.drawString(100, 0, String(average) + "mm");

    display.drawVerticalLine(int((fl_average/255)*127), 48, 16);
    drawArrow(34); //focus height
    display.display();
    delay(1);
}
