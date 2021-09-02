
#ifndef CONSTS

#define CONSTS
const int RELAY_IN_PIN = 8;
const int THERMOMETER_DATA_PIN = 0;
const int SERVO_DATA_PIN = 9;

const float SERVO_STEP_SIZE = 0.5;

const int SERVO_POSITION_DATA_ADDRESS = 0;
const float SAVING_SERVO_POSITION_DIFFERENCE = 10;

const int LIGHT_TIME = 20;
const int MIN_PAUSE = 30;
const double MAX_TEMPERATURE = 37.35;
const double MIN_TEMPERATURE = 37.30;

const unsigned long TEMPERATURE_MEASURES_ON_SECOND = 10;

const int AVERAGING_NUMBER = 100;

const unsigned long SERVO_STEP_DELAY = 10UL;
#endif
