#include <DS1302_module.h>

const int RST_PIN = 8;
const int DAT_PIN = 7;
const int CLK_PIN = 6;

DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);

bool fedMorning = false;
bool fedEvening = false;
bool skipMorningNextDay = false;

static int th1, tm1, th2, tm2;

void initTime(int xth1, int xtm1, int xth2, int xtm2)
{ // just for the FIRST use
    th1 = xth1;
    tm1 = xtm2;
    th2 = xth2;
    tm2 = xtm2;
    //   rtc.writeProtect(false);
    //   rtc.halt(false);

    //   Time t(2025, 8, 2, 11, 1, 0, Time::kSaturday);
    //   rtc.time(t);
}

static bool nowBeforeOrEqual(int nowH, int nowM, int H, int M)
{
    return (nowH < H) || (nowH == H && nowM <= M);
}

void onManualFeed()
{
    Serial.print(fedEvening+' '+fedMorning+' '+skipMorningNextDay);
    
    Time t = rtc.time();

    if (!fedMorning && nowBeforeOrEqual(t.hr, t.min, th1, tm1))
    { // before breakfast
        fedMorning = true;
        return;
    }

    if (!fedEvening && nowBeforeOrEqual(t.hr, t.min, th2, tm2))
    { // before dinner
        fedEvening = true;
        return;
    }

    skipMorningNextDay = true; // after dinner
}

bool isFeedTime()
{
    Time t = rtc.time(); // query the current time

    if (t.hr == th1 && t.min == tm1 && !fedMorning) // breakfast
    {
        if (skipMorningNextDay)
        {
            fedMorning = true;
            skipMorningNextDay = false;
            return false; // skip breakfast (dinner * 2)
        }
        fedMorning = true;
        return true; //do breakfast
    }

    if (t.hr == th2 && t.min == tm2 && !fedEvening) // dinner
    {
        fedEvening = true;
        return true;
    }

    // reset parameters at midnight
    if (t.hr == 0 && t.min == 1)
    {
        fedMorning = false;
        fedEvening = false;
    }

    return false;
}

void digitalClockDisplay()
{
    Time t = rtc.time(); // query the current time

    Serial.print("Time: ");

    if (t.hr < 10)
        Serial.print('0');
    Serial.print(t.hr);
    Serial.print(':');

    if (t.min < 10)
        Serial.print('0');
    Serial.print(t.min);
    Serial.print(':');

    if (t.sec < 10)
        Serial.print('0');
    Serial.println(t.sec);
}

Time currectTime()
{
    return rtc.time();
}