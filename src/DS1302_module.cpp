#include "DS1302_module.h"

const int RST_PIN = 8;
const int DAT_PIN = 7;
const int CLK_PIN = 6;

DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);

bool fedMorning = false;
bool fedEvening = false;

bool isFeedTime()
{
    Time t = rtc.time();

    if (t.hr == 8 && t.min == 0 && !fedMorning)
    {
        fedMorning = true;
        return true;
    }

    if (t.hr == 19 && t.min == 0 && !fedEvening)
    {
        fedEvening = true;
        return true;
    }
    if (t.hr == 0 && t.min == 1)
    {
        fedMorning = false;
        fedEvening = false;
    }

    return false;
}

void digitalClockDisplay()
{
    Time t = rtc.time();

    Serial.print("Time: ");

    // Hour
    if (t.hr < 10)
        Serial.print('0');
    Serial.print(t.hr);
    Serial.print(':');

    // Minute
    if (t.min < 10)
        Serial.print('0');
    Serial.print(t.min);
    Serial.print(':');

    // Second
    if (t.sec < 10)
        Serial.print('0');
    Serial.println(t.sec);
}