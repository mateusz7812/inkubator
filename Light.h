#ifndef LIGHT

#define LIGHT
#include "Arduino.h"

class Light
  {
  private:
      int pin;
      bool state;
      bool TURN_ON = true;
      bool TURN_OFF = false;
      
      void set_light_pin(int level){
        digitalWrite(pin, level);
      }
    
  public:
    Light(int relay_pin);

    bool get_state(){
      return state;
    }
    
    void turn_on();
    void turn_off();
  };

#endif