#include "consts.h"
#include "AbstractDisplay.h"
#include "Thermometer.h"
#include "Light.h"
#include "MyServo.h"
#include "SerialManager.h"


class Controller{
  protected:    
    double C = MAX_TEMPERATURE;
    Thermometer* thermometer;
    Light* light;
    MyServo * servo;
    MyClock * myClock;
    AbstractDisplay * display;
    Reporter * reporter;
    SerialManager * serial;
  public: 
    Controller(Thermometer* t, Light* l, MyServo* s, MyClock* c, AbstractDisplay* d, Reporter* r, SerialManager * m){
      thermometer = t;
      light = l;
      servo = s;
      myClock = c;
      display = d;
      reporter = r;
      serial = m;
    }
    virtual void setup() = 0;
    virtual void process() = 0;
};