#include "Light.h"

Light::Light(int relay_pin){  
      pin = relay_pin;
      pinMode(pin, OUTPUT);
      state = TURN_ON;
      turn_off();
    }


void Light::turn_on(){
    if (state != TURN_ON){
        state = TURN_ON;
        set_light_pin(LOW);
    }
}

void Light::turn_off(){
    if (state != TURN_OFF){
        state = TURN_OFF;
        set_light_pin(HIGH);
    }
}