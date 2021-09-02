#include "MyServo.h"

MyServo::MyServo(int servo_pin, float moving_difference, AbstractDataManager *data_manager)
{
    this->data_manager = data_manager;
    cur_pos = data_manager->read(SERVO_POSITION_DATA_ADDRESS);
    pin = servo_pin;
    difference = moving_difference;
    servo_attached = false;
    last_save = cur_pos;
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
        save_position_if_required();
    }
    else
    {
        detach_servo();
    }
    
}

void MyServo::save_position_if_required(){
    if (abs(cur_pos - last_save) > SAVING_SERVO_POSITION_DIFFERENCE)
    {
        data_manager->save((int)cur_pos, SERVO_POSITION_DATA_ADDRESS);
        last_save = cur_pos;
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
