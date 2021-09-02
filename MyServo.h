#ifndef SERVO

#define SERVO
#include <Servo.h>
#include <Arduino.h>
#include "consts.h"
#include "AbstractDataManager.h"

class MyServo
{
private:
  Servo myservo;
  AbstractDataManager *data_manager;
  int pin;
  float cur_pos;
  float last_save;
  float difference;
  bool servo_attached;
  void attach_servo();
  void detach_servo();
  bool move_required(float required_position);
  int get_flag(float required_position);
  void save_position_if_required();

public:
  MyServo(int servo_pin, float moving_difference, AbstractDataManager *data_manager);
  void move(float next_pos);
  void take_step(float next_pos);
};
#endif