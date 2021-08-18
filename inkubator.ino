#include "Thermometer.h"
#include "Reporter.h"
#include "Light.h"
#include "SerialManager.h"
#include "MyClock.h"
#include "MyServo.h"
#include "Controller.h"
#include "consts.h"
#include "MMController.h"
#include "SerialManager.h"
#include "Display.h"

Thermometer * thermo;
Light * light;
MyServo * servo;
MyClock * myClock;
SerialManager * serialM;
AbstractDisplay * display;
Reporter * reporter;

Controller * controller;

void setup(){
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  
  reporter = new Reporter();

  serialM = new SerialManager();
  reporter->setSerial(serialM);
  
  reporter->reportInfo(String("Display initialization ..."));
  display = new Display(reporter);
  reporter->reportInfo("Display initialization done");
  reporter->setDisplay(display);

  thermo = new Thermometer(analogPin);
  reporter->reportInfo("Thermometer initialization done");
  
  light = new Light(relaypin);
  reporter->reportInfo("Light initialization done");
  
  servo = new MyServo(9, 0, 0.5);
  reporter->reportInfo("Servo initialization done");
  
  myClock = new MyClock();
  reporter->reportInfo("Clock initialization done");

  reporter->reportInfo("Controller initialization...");
  controller = new MMController(thermo, light, servo, myClock, display, reporter, serialM);
  controller->setup();
  reporter->reportInfo("Controller initialization done");
}

void loop() { 
  controller->process();
  delay(1000);
}
