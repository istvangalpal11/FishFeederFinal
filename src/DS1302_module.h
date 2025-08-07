#ifndef DS1302_MODULE_H
#define DS1302_MODULE_H

#include <DS1302.h>
#include <Arduino.h>

void initTime(); //just for the first use
bool isFeedTime(); //verify if there is feeding time
void digitalClockDisplay(); //pretty print

#endif