#include "MyClock.h"

MyClock::MyClock(Reporter *reporter)
{
    rtc = new DS1302RTC(4, 2, 3);
    this->reporter = reporter;
}

tmElements_t MyClock::read()
{
    tmElements_t tm;
    rtc->read(tm);
    return tm;
}

int MyClock::set(time_t t)
{
    return rtc->set(t);
}

void MyClock::setClockTime(int s, int mi, int h, int d, int mo, int y)
{
    time_t t;
    tmElements_t tm;

    tm.Year = CalendarYrToTm(y);
    tm.Month = mo;
    tm.Day = d;
    tm.Hour = h;
    tm.Minute = mi;
    tm.Second = s;
    t = makeTime(tm);
    setTimeT(t);
}

void MyClock::moveTime(int offset)
{
    time_t t;
    tmElements_t tm = read();
    t = makeTime(tm);
    t += offset;
    setTimeT(t);
}

void MyClock::setTimeT(time_t t)
{
    set(t);
    setTime(t);
/*    if (set(t) == 0)
    {
        setTime(t);
        reporter->reportInfo("RTC set!\n");
    }
    else
    {
        reporter->reportError("RTC set failed!\n");
    }*/
}

bool getDate(tmElements_t *tm, const char *str)
{

    const char *monthName[12] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    char Month[12];
    int Day, Year;
    uint8_t monthIndex;

    if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3)
        return false;
    for (monthIndex = 0; monthIndex < 12; monthIndex++)
    {
        if (strcmp(Month, monthName[monthIndex]) == 0)
            break;
    }
    if (monthIndex >= 12)
        return false;
    tm->Day = Day;
    tm->Month = monthIndex + 1;
    tm->Year = CalendarYrToTm(Year);
    return true;
}

bool getTime(tmElements_t *tm, const char *str)
{
    int Hour, Min, Sec;

    if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3)
        return false;
    tm->Hour = Hour;
    tm->Minute = Min;
    tm->Second = Sec;
    return true;
}

void MyClock::setDateTime(const char *date, const char *time)
{
    tmElements_t tm;
    getTime(&tm, time);
    getDate(&tm, date);
    time_t t;
    t = makeTime(tm);
    setTimeT(t);
}