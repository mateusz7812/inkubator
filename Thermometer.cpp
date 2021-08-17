#include "Thermometer.h"
#include <Arduino.h>

double Thermometer::get_R(){
    raw = analogRead(pin);
    buffer = raw * Vin;
    Vout = (buffer)/1024.0;
    buffer = (Vin/Vout) - 1;
    R2 = R1 * buffer;
    return R2;
}

double Thermometer::measure(){
    R2 = get_R();
    R = R2 / 1000;
    R = 10-R;    
    return 4.72 * R + 21;
}