#ifndef DS1302_MODULE_H
#define DS1302_MODULE_H

#include <DS1302.h>
#include <Arduino.h>

void initTime(int xth1, int xtm1, int xth2, int xtm2); //just for the first use, setup
bool isFeedTime(); //verify if there is feeding time
void digitalClockDisplay(); //pretty print
void onManualFeed(); // mark the nearest upcoming schedule as don

Time currentTime();
#endif