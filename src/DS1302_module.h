#ifndef RTC_MODULE_H
#define RTC_MODULE_H

#include <DS1302.h>
#include <Arduino.h>

void initTime();
bool isFeedTime();
void digitalClockDisplay();

#endif