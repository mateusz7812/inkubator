
#ifndef THERMOMETER

#define THERMOMETER
#include "Arduino.h"

class Thermometer {
  private:
    int pin;
    double Vin = 5.0;
    double R1 = 10000;
    double R0 = 10000;
    double T0 = 25 + 273.15;
    double B = 3179.57;

  public:
    Thermometer(int analog_pin){
      pinMode(A1, OUTPUT);
      digitalWrite(A1, LOW);
      pinMode(A2, OUTPUT);
      digitalWrite(A2, HIGH);
      pin = analog_pin;
    }

    double get_R();
    double measure();
  };
#endif