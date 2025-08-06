#include <DS1302_module.h>

const int RST_PIN = 8;
const int DAT_PIN = 7;
const int CLK_PIN = 6;

DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);

bool fedMorning = false;
bool fedEvening = false;

int th1 = 12, tm1 = 40, th2 = 19, tm2 = 00;


void initTime() {  //just for the FIRST use
//   rtc.writeProtect(false);
//   rtc.halt(false);
  
//   Time t(2025, 8, 2, 11, 1, 0, Time::kSaturday);
//   rtc.time(t);
}

bool isFeedTime()
{
    Time t = rtc.time();  //query the current time

    if (t.hr == th1 && t.min == tm1 && !fedMorning)
    {
        fedMorning = true;
        return true;
    }

    if (t.hr == th2 && t.min == tm2 && !fedEvening)
    {
        fedEvening = true;
        return true;
    }

    //reset parameters at midnight
    if (t.hr == 0 && t.min == 1)
    {
        fedMorning = false;
        fedEvening = false;
    }

    return false;
}

void digitalClockDisplay()
{
    Time t = rtc.time();  //query the current time

    Serial.print("Time: ");

    if (t.hr < 10) Serial.print('0');
    Serial.print(t.hr);
    Serial.print(':');

    if (t.min < 10) Serial.print('0');
    Serial.print(t.min);
    Serial.print(':');

    if (t.sec < 10) Serial.print('0');
    Serial.println(t.sec);
}