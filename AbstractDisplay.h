#ifndef ABSTRACT_DISPLAY

#define ABSTRACT_DISPLAY
#include <Arduino.h>

class AbstractDisplay{
    public:
        virtual void displayData(char temperature[], char date[], bool light_state, char maxc[]) = 0;
        virtual void displayError(char message[]) = 0;
};
#endif