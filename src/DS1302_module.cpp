#include <DS1302_module.h>
#include <EEPROM.h>

const int RST_PIN = 8;
const int DAT_PIN = 7;
const int CLK_PIN = 6;

DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);

bool didResetToday = false;
bool fedMorning = false;
bool fedEvening = false;
bool skipMorningNextDay = false;

static const uint8_t EE_SKIP = 0;  // one byte for skip flag

static void saveSkip() { EEPROM.update(EE_SKIP, skipMorningNextDay ? 1 : 0); }
static void loadSkip() { skipMorningNextDay = EEPROM.read(EE_SKIP) == 1; }

static int th1, tm1, th2, tm2;

void initTime(int xth1, int xtm1, int xth2, int xtm2)
{
    th1 = xth1;
    tm1 = xtm1;
    th2 = xth2;
    tm2 = xtm2;

    loadSkip(); //stored in EEPROM

    //   rtc.writeProtect(false);       // just for the FIRST use
    //   rtc.halt(false);

    //   Time t(2025, 8, 2, 11, 1, 0, Time::kSaturday);
    //   rtc.time(t);
}

void initFlags() {
  Time t = rtc.time();

  // fedMorning = true if we are AT/AFTER breakfast time
  if (t.hr > th1 || (t.hr == th1 && t.min >= tm1)) {
    fedMorning = true;
  } else {
    fedMorning = false;
    fedEvening = false;
  }

  // fedEvening = true if we are AT/AFTER dinner time
  if (t.hr > th2 || (t.hr == th2 && t.min >= tm2)) {
    fedEvening = true;
    return;
  } else {
    fedEvening = false;
    return;
  }
}

static bool nowBeforeOrEqual(int nowH, int nowM, int H, int M)
{
    return (nowH < H) || (nowH == H && nowM <= M);
}

// if the button is pressed multiple times, just 1 scheduled feeding will be skipped
void onManualFeed()
{
    Time t = rtc.time(); // queary the current time

    if (!fedMorning && nowBeforeOrEqual(t.hr, t.min, th1, tm1))
    { // before breakfast, we skip the scheduled breakfast
        fedMorning = true;
        return;
    }

    if (!fedEvening && nowBeforeOrEqual(t.hr, t.min, th2, tm2))
    { // before dinner, we skip the scheduled dinner
        fedEvening = true;
        return;
    }

    skipMorningNextDay = true; // after dinner, that means we will skip the next morning
    saveSkip();
}

// scheduled feeding
bool isFeedTime()
{
    Time t = rtc.time(); // query the current time
    if (t.hr == th1 || t.hr == th2)
    {
        if (t.hr == th1 && t.min == tm1 && !fedMorning) // breakfast
        {
            if (skipMorningNextDay) // they was fed yesterday after dinner
            {
                fedMorning = true;
                skipMorningNextDay = false;
                saveSkip();
                return false; // skip breakfast
            }
            fedMorning = true;
            return true; // do breakfast
        }
        if (t.hr == th2 && t.min == tm2 && !fedEvening) // dinner
        {
            fedEvening = true;
            return true;
        }
    }

    // reset parameters at midnight
    if (t.hr == 0 && t.min <= 3 && !didResetToday)
    {
        fedEvening=false;
        fedMorning=false;

        didResetToday = true;
    }
    if (t.hr == 0 && t.min == 10)
    { // clear the one-shot latch later
        didResetToday = false;
    }

    return false; // means no feeding time
}

void digitalClockDisplay() // helper
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

Time currentTime()
{
    return rtc.time();
}