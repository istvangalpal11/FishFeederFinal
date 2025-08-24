#ifndef DS1302_MODULE_H
#define DS1302_MODULE_H

#include <DS1302.h>
#include <Arduino.h>

void initTime(int xth1, int xtm1, int xth2, int xtm2); //first use + feeding time setup

bool isFeedTime(); //verify if there is feeding time

void onManualFeed(); // mark the nearest upcoming schedule as don

Time currentTime(); //if other parts of code needs the current time

void digitalClockDisplay(); //pretty print, helper
#endif