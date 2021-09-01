#ifndef SERVO

#define SERVO
#include <Servo.h>
#include <Arduino.h>
#include "consts.h"

class MyServo{
  private:
    Servo myservo;
    int pin;
    float cur_pos;
    float difference;
    bool servo_attached;
    void attach_servo();
    void detach_servo();
    bool move_required(float required_position);
    int get_flag(float required_position);
  public:
    MyServo(int servo_pin, float start_pos, float moving_difference);
    void move(float next_pos);
    void take_step(float next_pos);
};
#endif