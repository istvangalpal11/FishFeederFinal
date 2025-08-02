#include <Arduino.h>
#include "DS1302_module.h"
#include "fan_relay_module.h"

void setup() {
  Serial.begin(9600);
  initTime();
  initFan();
}

void loop() {
  if (isFeedTime()) {
    Serial.println("Feeding time!!"); //another function later
  }

  digitalClockDisplay();
  
  testFan();
}