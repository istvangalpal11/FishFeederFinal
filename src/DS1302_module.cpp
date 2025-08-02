#include <Arduino.h>
#include <DS1302.h>

const int RST_PIN = 8;
const int DAT_PIN = 7;
const int CLK_PIN = 6;

DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);

bool fedMorning = false;
bool fedEvening = false;

void initTime() {
//   rtc.writeProtect(false);
//   rtc.halt(false);
  
//   Time t(2025, 8, 2, 11, 1, 0, Time::kSaturday);
//   rtc.time(t);
}

bool isFeedTime()
{
    Time t = rtc.time();  // Frissítjük az időt

    if (t.hr == 11 && t.min == 3 && !fedMorning)
    {
        fedMorning = true;
        return true;
    }

    if (t.hr == 19 && t.min == 0 && !fedEvening)
    {
        fedEvening = true;
        return true;
    }

    // Éjfél után 1 perccel újraengedélyezzük az etetést
    if (t.hr == 0 && t.min == 1)
    {
        fedMorning = false;
        fedEvening = false;
    }

    return false;
}

void digitalClockDisplay()
{
    Time t = rtc.time();  // Lekérjük az időt

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