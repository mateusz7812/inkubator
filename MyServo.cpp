#include "MyServo.h"

MyServo::MyServo(int servo_pin, float start_pos, float moving_difference){
    pin = servo_pin;
    cur_pos = start_pos;
    difference = moving_difference;
}

void MyServo::move(float next_pos){
    float flag = 2 * (cur_pos < next_pos) - 1;
    myservo.attach(pin); 
    while (abs(cur_pos - next_pos) > difference){
        cur_pos += (difference * flag);
        myservo.write(cur_pos);              
        delay(10);                       
    }
    myservo.detach();
} 