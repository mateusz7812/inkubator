#ifndef MMCONTROLLER

#define MMCONTROLLER
#include "Controller.h"
#include "MemoryFree.h"
#include <Time.h>
//#include <stdio.h>

class MMController : public Controller
{
private:
  double maxc = 0;
  double minc = 40;
  char power_on_time[30];
  double light_counter = 0;
  bool light_delay_flag = false;
  bool light_state = true;
  unsigned long actual_time = 0;
  unsigned long display_time = 0;
  unsigned long thermometer_time = 0;
  unsigned long light_time = 0;
  unsigned long led_time = 0;
  unsigned long servo_time = 0;
  unsigned long temperature_measure_delay = 1000UL / TEMPERATURE_MEASURES_ON_SECOND;

  void text2digits(char str[], int number);
  void switchLight();
  void saveMaxTemp();
  void rotateEggs();
  bool timeToRotate();
  void printData();
  void measureTemperature();

public:
  MMController(Thermometer *t, Light *l, MyServo *s, MyClock *c, AbstractDisplay *d, Reporter *r, SerialManager *m);
  void setup() override;
  void process() override;
};

#endif