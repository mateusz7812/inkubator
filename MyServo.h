#ifndef SERVO

#define SERVO
#include <Servo.h>
#include <Arduino.h>

class MyServo{
  private:
    Servo myservo;
    int pin;
    float cur_pos;
    float difference;
  public:
    MyServo(int servo_pin, float start_pos, float moving_difference);
    void move(float next_pos);
};
#endif