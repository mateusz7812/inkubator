#include "MyClock.h"

MyClock::MyClock(Reporter * reporter){
    rtc = new DS1302RTC(4, 2, 3); 
    this->reporter = reporter;
}

tmElements_t MyClock::read(){
    tmElements_t tm;
    rtc->read(tm);
    return tm;
}

int MyClock::set(time_t t){
    return rtc->set(t);
}

void MyClock::setClockTime(int s, int mi, int h, int d, int mo, int y){
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

void MyClock::moveTime(int offset){
    time_t t;
    tmElements_t tm = read();
    t = makeTime(tm);
    t += offset;
    setTimeT(t);
}

void MyClock::setTimeT(time_t t){
    if(set(t) == 0) {
    setTime(t);
    reporter->reportInfo("RTC set!\n");
    }
    else {
    reporter->reportError("RTC set failed!\n");
    }
}