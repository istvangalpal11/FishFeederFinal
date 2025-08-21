#include "button_feed.h"
#include "feeder_module.h"
#include "DS1302_module.h"

static int buttonPin;
static bool *isFeeding;

void initFeedButton(int pin, bool* feedingFlag) {
  buttonPin = pin;
  isFeeding = feedingFlag;
  pinMode(buttonPin, INPUT_PULLUP);
}

void checkFeedButton() {
  if (buttonPin = 0 || isFeeding == nullptr) return; //not set yet

  // Button pressed (PULLUP logic: LOW = pressed)
  if (digitalRead(buttonPin) == LOW && !(*isFeeding)) {
    *isFeeding = true;
    feedingProcess();
    onManualFeed();
    *isFeeding = false;
  }
}

