#include "MMController.h"

MMController::MMController(Thermometer* t, Light* l, MyServo* s, MyClock* c, AbstractDisplay* d, Reporter* r, SerialManager* m): Controller(t, l, s, c, d, r, m)
{  
    tmElements_t tm = myClock->read();
    String text = text2digits(tm.Hour) + ':' + text2digits(tm.Minute) + ':' + text2digits(tm.Second) + " " + tm.Day + "/" + tm.Month + "/" + tmYearToCalendar(tm.Year);
    power_on_time = text;
    servo->move(1);
}


String MMController::text2digits(int number) {
    String n = String(number);
    if (number >= 0 && number < 10)
    n = String('0') + n;
    return n;
}

void MMController::setup(){
    delay(1000); 
    Serial.print("Power on!\n");
    
    //myClock->setClockTime(0,51,14,16,8,2021);
    //myClock->moveTime(-1);
}

void MMController::process() {
    temp = thermometer->measure();
    C = (C + temp) / 2;

    tmElements_t tm = myClock->read();
    String text = text2digits(tm.Hour) + ':' + text2digits(tm.Minute) + ':' + text2digits(tm.Second);

    saveMaxTemp();
    display->displayData(String(C), text);
    printData();
    switchLight();
    rotateEggs();
}

void MMController::switchLight(){
    if(light_counter >= 10){
        light_delay_flag = true;
    }
    else if(light_counter <= 0){
        light_delay_flag = false;
    }

    if((!light_delay_flag) && (C < MIN_TEMPERATURE)){
        light->turn_on();
        light_counter++;
    }
    else if(light_delay_flag || (C > MAX_TEMPERATURE)){
        light->turn_off();
        light_counter--;
    }
}

void MMController::saveMaxTemp(){
    if(C > maxc){
    maxc = C;
    }
    else if (C < minc){
    minc = C;
    };
}

void MMController::rotateEggs(){
    if(timeToRotate()){
    servo->move(0);
    }else{
    servo->move(180);
    }
}

bool MMController::timeToRotate(){
    tmElements_t tm = myClock->read();
    return (tm.Hour+4) % 24 < 12;
}

void MMController::printData(){
    double resistance = thermometer->get_R();
    String str = power_on_time + " " + C + " " + resistance + " " + maxc + " " + minc + " " + MAX_TEMPERATURE + " " + MIN_TEMPERATURE + " ";
    if (light->get_state())
        str += "ON ";
    else
        str += "OFF ";
    str += String(serial->readFloat()) + "\n";
    reporter->reportInfo(str);
}


