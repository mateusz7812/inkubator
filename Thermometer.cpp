#include "Thermometer.h"
#include <Arduino.h>

double Thermometer::get_R(){
    double R2;
    double buffer;
    int raw;
    double Vout;

    raw = analogRead(pin);
    buffer = raw * Vin;
    Vout = (buffer)/1023.0;
    buffer = (Vin/Vout) - 1;
    R2 = R1 * buffer;
    return R2;
}

double Thermometer::measure(){
    double R = get_R();

    double ln = log(R / R0);
    double t =  (1 / ((ln / B) + (1 / T0)));
    t -= 273.15; // from K to C
    return t;
}