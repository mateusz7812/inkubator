
#ifndef REPORTER

#define REPORTER
#include <Arduino.h>
#include "AbstractDisplay.h"
#include "SerialManager.h"

class Reporter
{
private:
    SerialManager *serialM;
    int pin;
    AbstractDisplay *display;
    bool led_state;
    void errorBlinking(int pin);

    void sendThreeBlinks(int s, int pin);
    void sendBlink(int s, int pin);

public:
    void setPin(int pin);
    void setSerial(SerialManager *serial);
    void setDisplay(AbstractDisplay *display);
    void reportError(char message[]);
    void reportInfo(char message[]);
    void led_on();
    void led_off();
};

#endif