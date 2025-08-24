#ifndef BUTTON_FEED_MODULE_H
#define BUTTON_FEED_MODULE_H

#include <Arduino.h>

//  - pin: the input pin for the button (with INPUT_PULLUP).
//  - feedingFlag: pointer to your global isFeeding flag in main.cpp
void initFeedButton(int pin, bool* feedingFlag);

void checkFeedButton();

#endif