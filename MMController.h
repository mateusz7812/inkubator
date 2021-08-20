#ifndef MMCONTROLLER

#define MMCONTROLLER
#include "Controller.h"

class MMController: public Controller{
  private:
    double maxc = 0;
    double minc = 40;
    double temp;
    String power_on_time;
    int light_counter = 0;
    bool light_delay_flag = false;
    
    String text2digits(int number);
    void switchLight();
    void saveMaxTemp();
    void rotateEggs();
    bool timeToRotate();
    void printData();

  public:
    MMController(Thermometer* t, Light* l, MyServo* s, MyClock* c, AbstractDisplay* d, Reporter* r, SerialManager* m);
    void setup() override;
    void process() override;
};

#endif