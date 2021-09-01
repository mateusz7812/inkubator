#include "MyServo.h"

MyServo::MyServo(int servo_pin, float start_pos, float moving_difference)
{
    pin = servo_pin;
    cur_pos = start_pos;
    difference = moving_difference;
    servo_attached = false;
}

void MyServo::move(float next_pos)
{
    do
    {
        take_step(next_pos);
    } while (move_required(next_pos));
}

void MyServo::take_step(float next_pos)
{
    if (move_required(next_pos))
    {
        attach_servo();
        cur_pos += (difference * get_flag(next_pos));
        myservo.write(cur_pos);
        delay(SERVO_STEP_DELAY);
    }
    else
    {
        detach_servo();
    }
}

void MyServo::attach_servo()
{
    if (!servo_attached)
    {
        myservo.attach(pin);
        servo_attached = true;
    }
}

void MyServo::detach_servo()
{
    if (servo_attached)
    {
        myservo.detach();
        servo_attached = false;
    }
}

bool MyServo::move_required(float required_position)
{
    return abs(cur_pos - required_position) > difference;
}

int MyServo::get_flag(float required_position)
{
    return 2 * (cur_pos < required_position) - 1;
}
