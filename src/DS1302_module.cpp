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

// EEPROM layout: [0]=MAGIC, [1]=FLAGS, [2]=~FLAGS
static const uint8_t EE_ADDR_MAGIC = 0;
static const uint8_t EE_ADDR_FLAGS = 1;
static const uint8_t EE_ADDR_INV = 2;
static const uint8_t MAGIC_BYTE = 0xA5;

static uint8_t packFlags()
{
    uint8_t f = 0;
    if (fedMorning)
        f |= 0x01;
    if (fedEvening)
        f |= 0x02;
    if (skipMorningNextDay)
        f |= 0x04;
    return f;
}

static void unpackFlags(uint8_t f)
{
    fedMorning = f & 0x01;
    fedEvening = f & 0x02;
    skipMorningNextDay = f & 0x04;
}

static void saveFlags()
{
    uint8_t f = packFlags();
    // Write only when different (update does this check internally)
    EEPROM.update(EE_ADDR_MAGIC, MAGIC_BYTE);
    EEPROM.update(EE_ADDR_FLAGS, f);
    EEPROM.update(EE_ADDR_INV, (uint8_t)~f);
}

static void loadFlags()
{
    uint8_t m = EEPROM.read(EE_ADDR_MAGIC);
    uint8_t f = EEPROM.read(EE_ADDR_FLAGS);
    uint8_t i = EEPROM.read(EE_ADDR_INV);
    if (m == MAGIC_BYTE && (uint8_t)~f == i)
    {
        unpackFlags(f);
    }
    else
    {
        // First run or corrupted EEPROM → initialize defaults and persist
        fedMorning = false;
        fedEvening = false;
        skipMorningNextDay = false;
        saveFlags();
    }
}

static int th1, tm1, th2, tm2;

void initTime(int xth1, int xtm1, int xth2, int xtm2)
{
    th1 = xth1;
    tm1 = xtm1;
    th2 = xth2;
    tm2 = xtm2;
    //   rtc.writeProtect(false);       // just for the FIRST use
    //   rtc.halt(false);

    //   Time t(2025, 8, 2, 11, 1, 0, Time::kSaturday);
    //   rtc.time(t);
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
        saveFlags();
        return;
    }

    if (!fedEvening && nowBeforeOrEqual(t.hr, t.min, th2, tm2))
    { // before dinner, we skip the scheduled dinner
        fedEvening = true;
        saveFlags();
        return;
    }

    skipMorningNextDay = true; // after dinner, that means we will skip the next morning
    saveFlags();
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
                saveFlags();
                return false; // skip breakfast
            }
            fedMorning = true;
            saveFlags();
            return true; // do breakfast
        }
        if (t.hr == th2 && t.min == tm2 && !fedEvening) // dinner
        {
            fedEvening = true;
            saveFlags();
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