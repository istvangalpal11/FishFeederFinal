#include <Arduino.h>
#include "DS1302_module.h"

void setup() {
  Serial.begin(9600);
  initTime();
}

void loop() {
  if (isFeedTime()) {
    Serial.println("Etetés ideje van! 🐟");
  }

  digitalClockDisplay();
  delay(1000);
}