#include "Reporter.h"
#include <Arduino.h>

void Reporter::setPin(int pin){
    pinMode(pin, OUTPUT);
    this->pin = pin;
}

void Reporter::setSerial(SerialManager * serial){
    this->serialM = serial;
}

void Reporter::setDisplay(AbstractDisplay * display){
    this->display = display;
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

void Reporter::reportError(String message){
  if(serialM != nullptr){
      serialM->print("Error: " + message);
  }
  if(display != nullptr){
      display->displayError(message);
  }
  if(pin != 0){
      errorBlinking(pin);
  }
}

void Reporter::reportInfo(String message){
  if(serialM != nullptr){
      serialM->print("Info: " + message);
  }
}