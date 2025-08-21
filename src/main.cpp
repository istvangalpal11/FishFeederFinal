#include <Arduino.h>
#include "DS1302_module.h"
#include "fan_relay_module.h"
#include "MG996R_module.h"
#include "feeder_module.h"
#include "button_feed.h"

bool isFeeding = false; //check if there is a feeding process currently
int buttonPin = 13;
int th1=8, tm1=0, th2=19, tm2=0;

void setup() {
  Serial.begin(9600);
  initTime(th1,tm1,th2,tm2);
  initFan();
  initServo();
  initFeedButton(buttonPin, &isFeeding);
}

void loop() {
  //button for force-feeding
  bool currentState = digitalRead(buttonPin);
  if (digitalRead(buttonPin)==LOW && isFeeding==false) {
    isFeeding=true;
    feedingProcess(); //start the feeding, aporx.3 min
    isFeeding=false;
  }

  //scheduled feeding
  if (isFeedTime() ) {
    feedingProcess();
  }

  //digitalClockDisplay();
}