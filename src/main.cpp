#include <Arduino.h>
#include "DS1302_module.h"
#include "fan_relay_module.h"
#include "MG996R_module.h"
#include "feeder_module.h"

void setup() {
  Serial.begin(9600);
  initTime();
  initFan();
  initServo();
}

void loop() {
  //if (isFeedTime()) {
    feedingProcess();
  //}
  digitalClockDisplay();

  delay(100000);
}