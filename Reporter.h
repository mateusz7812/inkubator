
#ifndef REPORTER

#define REPORTER
#include <Arduino.h>
#include "AbstractDisplay.h"
#include "SerialManager.h"

class Reporter {
    private:
        SerialManager * serialM;
        int pin;
        AbstractDisplay * display;
    public:
        void setPin(int pin);
        void setSerial(SerialManager * serial);
        void setDisplay(AbstractDisplay * display);
        void reportError(String message);
        void reportInfo(String message);
};

#endif