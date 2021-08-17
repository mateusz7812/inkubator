#include "ErrorReporter.h"

void ErrorReporter::setPin(int pin){
    pinMode(pin, OUTPUT);
    self.pin = pin;
}

void ErrorReporter::setStream(Stream * stream){
    self.stream = stream;
}

void ErrorReporter::setDisplay(Display * display){
    seld.display = display;
}

void sendBlink(int s, int pin){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(s);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(300);  
}

void sendThreeBlinks(int s, int pin){
  for(int i = 0; i<3; i++){
    sendBlink(s, pin);
  }
}

void errorBlinking(int pin){
  for(;;){
   sendThreeBlinks(150, pin);
   sendThreeBlinks(400, pin);
   sendThreeBlinks(150, pin); 
   delay(1000);  
  }
}

void ErrorReporter::reportError(string message){
    if(stream != nullptr){
        stream->write(message);
    }
    if(display != nullptr){
        display->displayError(message);
    }
    if(pin != 0){
        errorBlinking(pin);
    }
}