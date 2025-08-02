#ifndef DS1302_MODULE_H
#define DS1302_MODULE_H

#include <DS1302.h>
#include <Arduino.h>

void initTime();
bool isFeedTime();
void digitalClockDisplay();

#endif