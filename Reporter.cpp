#include "Reporter.h"
#include <Arduino.h>

void Reporter::setPin(int pin)
{
  pinMode(pin, OUTPUT);
  this->pin = pin;
}

void Reporter::setSerial(SerialManager *serial)
{
  this->serialM = serial;
}

void Reporter::setDisplay(AbstractDisplay *display)
{
  this->display = display;
}

void Reporter::led_on()
{
  if (!led_state)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    led_state = true;
  }
}

void Reporter::led_off()
{
  if (led_state)
  {
    digitalWrite(LED_BUILTIN, LOW);
    led_state = false;
  }
}

void Reporter::sendBlink(int s, int pin)
{
  led_on();
  delay(s);
  led_off();
  delay(300);
}

void Reporter::sendThreeBlinks(int s, int pin)
{
  for (int i = 0; i < 3; i++)
  {
    sendBlink(s, pin);
  }
}

void Reporter::errorBlinking(int pin)
{
  for (int i = 0; i < 3; i++)
  {
    sendThreeBlinks(150, pin);
    sendThreeBlinks(400, pin);
    sendThreeBlinks(150, pin);
    delay(1000);
  }
}

void Reporter::reportError(char message[])
{
  while (true)
  {
    if (serialM != nullptr)
    {
      serialM->print("Error: ");
      serialM->print(message);
    }
    if (display != nullptr)
    {
      display->displayError(message);
    }
    if (pin != 0)
    {
      errorBlinking(pin);
    }
  }
}

void Reporter::reportInfo(char message[])
{
  if (serialM != nullptr)
  {
    serialM->print("Info: ");
    serialM->print(message);
  }
}