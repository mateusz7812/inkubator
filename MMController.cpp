#include "MMController.h"

MMController::MMController(Thermometer *t, Light *l, MyServo *s, MyClock *c, AbstractDisplay *d, Reporter *r, SerialManager *m) : Controller(t, l, s, c, d, r, m)
{
    tmElements_t tm = myClock->read();
    char date[30];
    /*text2digits(date, tm.Hour);
    strcat(date, ':');
    text2digits(date, tm.Minute);
    strcat(date, ':');
    text2digits(date, tm.Second);
    strcat(date, " ");
    text2digits(date, tm.Day);
    strcat(date, '/');
    text2digits(date, tm.Month);
    strcat(date, '/');
    strcat(date, tmYearToCalendar(tm.Year));
    strcpy(power_on_time, date);*/
}

void MMController::setup()
{
    //myClock->setDateTime(__DATE__, __TIME__);
    //myClock->moveTime(50);
    C = thermometer->measure();
}

void MMController::process()
{
    actual_time = millis();

    if (actual_time - thermometer_time >= temperature_measure_delay)
    {
        thermometer_time = actual_time;
        measureTemperature();
        saveMaxTemp();
    }

    if (actual_time - display_time >= 1000UL)
    {
        display_time = actual_time;

        tmElements_t tm = myClock->read();
        char additional[128];
        char maxc_str[5];
        dtostrf(maxc, 0, 2, maxc_str);
        sprintf(additional, "%02d:%02d:%02d %s", tm.Hour, tm.Minute, tm.Second, maxc_str);

        char temperature[5];
        dtostrf(C, 0, 2, temperature);
        display->displayData(temperature, additional, light_state);
    }

    if (actual_time - light_time >= SWITCH_LIGHT_DELAY)
    {
        light_time = actual_time;
        switchLight();
    }

    if (actual_time - servo_time >= SERVO_STEP_DELAY)
    {
        servo_time = actual_time;
        rotateEggs();
    }

    if (actual_time - led_time >= 1000UL)
    {
        led_time = actual_time;
        reporter->led_on();
    }
    else if (actual_time - led_time >= 500UL)
    {
        reporter->led_off();
    }
}

void MMController::measureTemperature()
{
    double temp = thermometer->measure();
    C = ((AVERAGING_NUMBER * C) + temp) / (AVERAGING_NUMBER + 1);
}

void MMController::switchLight()
{
    if (light_counter >= 10)
    {
        light_delay_flag = true;
    }
    else if (light_counter <= 0)
    {
        light_delay_flag = false;
    }

    if ((C > 17) && (C < 40) && (!light_delay_flag) && (C < MIN_TEMPERATURE))
    {
        light->turn_on();
        light_state = true;
        light_counter++;
    }
    else if (light_delay_flag || (C > MAX_TEMPERATURE))
    {
        light->turn_off();
        light_state = false;
        light_counter -= LIGHT_COUNTER_PENALTY;
        if (light_counter < 0)
        {
            light_counter = 0;
        }
    }
    else if ((C >= MIN_TEMPERATURE) && (C <= MAX_TEMPERATURE))
    {
        //buffer zone
    }
    else
    {
        light->turn_off();
        reporter->reportError("Temperature error!");
    }
}

void MMController::saveMaxTemp()
{
    if (C > maxc)
    {
        maxc = C;
    }
    else if (C < minc)
    {
        minc = C;
    };
}

void MMController::rotateEggs()
{
    if (timeToRotate())
    {
        servo->take_step(0);
    }
    else
    {
        servo->take_step(180);
    }
}

bool MMController::timeToRotate()
{
    tmElements_t tm = myClock->read();
    return (tm.Hour + 4) % 24 < 12;
}

void MMController::printData()
{
    /*
    char resistance[10];
    dtostrf(thermometer->get_R(), 10, 2, resistance);

    char light_str[4];
    if (light->get_state())
        light_str = "ON";
    else
        light_str = "OFF";

    char read_temp[10];
    dtostrf(serial->readFloat(), 10, 2, read_temp);

    char C_str[10];
    dtostrf(C, 10, 2, C_str);

    char str[70];
    sprintf(str, "%s| %s %s", power_on_time, C_str, resistance, maxc, minc, MAX_TEMPERATURE, MIN_TEMPERATURE, light_str, read_temp);

    reporter->reportInfo(str);*/
}
