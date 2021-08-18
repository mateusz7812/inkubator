
#ifndef SERIAL_MANAGER

#define SERIAL_MANAGER
#include <Arduino.h>

class SerialManager{
    public:
        SerialManager(){
            Serial.begin(9600);
        }
        
        void print(String str){
            Serial.print(str.c_str());
        }

        float readFloat(){
            return Serial.parseFloat();
        }

};

#endif