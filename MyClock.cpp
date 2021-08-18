#include "MyClock.h"

MyClock::MyClock(){
    rtc = new DS1302RTC(4, 2, 3); 
}

tmElements_t MyClock::read(){
    tmElements_t tm;
    rtc->read(tm);
    return tm;
}

int MyClock::set(time_t t){
    return rtc->set(t);
}
