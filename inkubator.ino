#include "MMController.h"
#include "Thermometer.h"
#include "Reporter.h"
#include "Light.h"
#include "SerialManager.h"
#include "MyClock.h"
#include "MyServo.h"
#include "Controller.h"
#include "SerialManager.h"
#include "Display.h"
#include "EepromManager.h"

Thermometer * thermo;
Light * light;
MyServo * servo;
MyClock * myClock;
SerialManager * serialM;
AbstractDisplay * display;
Reporter * reporter;
AbstractDataManager * data_manager;

Controller * controller;

void setup(){
  
  reporter = new Reporter();
  data_manager = new EepromManager(reporter);

  serialM = new SerialManager();
  reporter->setSerial(serialM);
  
  reporter->reportInfo("Display initialization ...\n");
  display = new Display(reporter);
  reporter->reportInfo("Display initialization done\n");
  reporter->setDisplay(display);

  thermo = new Thermometer(THERMOMETER_DATA_PIN);
  reporter->reportInfo("Thermometer initialization done\n");
  
  light = new Light(RELAY_IN_PIN);
  reporter->reportInfo("Light initialization done\n");
  
  servo = new MyServo(SERVO_DATA_PIN, SERVO_STEP_SIZE, data_manager);
  reporter->reportInfo("Servo initialization done\n");
  
  myClock = new MyClock(reporter);
  reporter->reportInfo("Clock initialization done\n");

  reporter->reportInfo("Controller initialization...\n");
  controller = new MMController(thermo, light, servo, myClock, display, reporter, serialM);
  controller->setup();
  reporter->reportInfo("Controller initialization done\n");
}

void loop() { 
  controller->process();
}
