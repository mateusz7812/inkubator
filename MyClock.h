#ifndef CLOCK

#define CLOCK
#include <DS1302RTC.h>
#include "Reporter.h"

class MyClock{
  private:
    DS1302RTC * rtc;
    Reporter * reporter;
    int set(time_t t);
    
  public:
    MyClock(Reporter * reporter);
    tmElements_t read();
    
    void setClockTime(int s, int mi, int h, int d, int mo, int y);
    void moveTime(int offset);
    void setTimeT(time_t t);
};
#endif