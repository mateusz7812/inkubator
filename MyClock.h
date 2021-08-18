#include <DS1302RTC.h>

class MyClock{
  protected:
    DS1302RTC * rtc;
  public:
    MyClock();
    tmElements_t read();
    int set(time_t t);
};