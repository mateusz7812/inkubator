#include <Servo.h>
#include <DS1302RTC.h>
#include <Adafruit_SSD1306.h>
#include "Thermometer.h"

int relaypin = 8;
int analogPin = 0;

int LIGHT_TIME = 20;
int MIN_PAUSE = 30;
double MAX_TEMPERATURE = 37.2;
double MIN_TEMPERATURE = 37.2;



class Light
  {
  private:
      int pin;
      bool state;
      bool TURN_ON = true;
      bool TURN_OFF = false;
      
      void set_light_pin(int level){
        digitalWrite(pin, level);
      }
    
  public:
    Light(int relay_pin){  
      pin = relay_pin;
      pinMode(pin, OUTPUT);
      state = TURN_ON;
      turn_off();
    }

    bool get_state(){
      return state;
    }
    
    void turn_on(){
      if (state != TURN_ON){
        Serial.println("light turned on");
        state = TURN_ON;
        set_light_pin(LOW);
      }
    }
    
    void turn_off(){
      if (state != TURN_OFF){
        Serial.println("light turned off");
        state = TURN_OFF;
        set_light_pin(HIGH);
      }
    }
  };

class MyServo{
  private:
    Servo myservo;
    int pin;
    float cur_pos;
    float difference;
  public:
    MyServo(int servo_pin, float start_pos, float moving_difference){
      pin = servo_pin;
      cur_pos = start_pos;
      difference = moving_difference;
    }
  
    void move(float next_pos){
      float flag = 2 * (cur_pos < next_pos) - 1;
      myservo.attach(pin); 
      while (abs(cur_pos - next_pos) > difference){
        cur_pos += (difference * flag);
        myservo.write(cur_pos);              
        delay(10);                       
      }
      myservo.detach();
    } 
};

class MyClock{
  protected:
    DS1302RTC * rtc;
  public:
    MyClock(){
      rtc = new DS1302RTC(4, 2, 3); 
    }

    tmElements_t read(){
      tmElements_t tm;
      rtc->read(tm);
      return tm;
    }

    int set(time_t t){
      return rtc->set(t);
    }
};

class Controller{
  protected:    
    double C = MAX_TEMPERATURE;
    Thermometer* thermometer;
    Light* light;
    MyServo * servo;
    MyClock * myClock;
    Adafruit_SSD1306 * display;
  public: 
    Controller(Thermometer* t, Light* l, MyServo* s, MyClock* c, Adafruit_SSD1306* d){
      thermometer = t;
      light = l;
      servo = s;
      myClock = c;
      display = d;
    }
    virtual void setup() = 0;
    virtual void process() = 0;
};

class MMController: public Controller{
  private:
    double maxc = 0;
    double minc = 40;
    double temp;
    String power_on_time;
  public:
    MMController(Thermometer* t, Light* l, MyServo* s, MyClock* c, Adafruit_SSD1306* d): Controller(t, l, s, c, d)
    {  
      tmElements_t tm = myClock->read();
      String text = print2digits(tm.Hour) + ':' + print2digits(tm.Minute) + ':' + print2digits(tm.Second) + " " + tm.Day + "/" + tm.Month + "/" + tmYearToCalendar(tm.Year);
      power_on_time = text;
      servo->move(1);
    }
    
    String print2digits(int number) {
      String n = String(number);
      if (number >= 0 && number < 10)
        n = String('0') + n;
      return n;
    }
    
    virtual void setup(){
      delay(1000); 
      Serial.print("Power on!\n");
      
      if(!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        errorBlinking();
      }
      
      display->setTextColor(SSD1306_WHITE);
      display->cp437(true); 
      //setClockTime(0,51,14,16,8,2021);
      //moveTime(-1);
    }
    
    void setClockTime(int s, int mi, int h, int d, int mo, int y){
      time_t t;
      tmElements_t tm;

      tm.Year = CalendarYrToTm(y);
      tm.Month = mo;
      tm.Day = d;
      tm.Hour = h;
      tm.Minute = mi;
      tm.Second = s;
      t = makeTime(tm);
      setT(t);
    }

    void moveTime(int offset){
      time_t t;
      tmElements_t tm = myClock->read();
      t = makeTime(tm);
      t += offset;
      setT(t);
    }

    void setT(time_t t){
      if(myClock->set(t) == 0) {
        setTime(t);
        printData();
      }
      else {
        Serial.print("RTC set failed!\n");
      }
    }
    
    virtual void process(){
      temp = thermometer->measure();
      C = (C + temp) / 2;

      saveMaxTemp();
      switchLight();
      rotateEggs();
      displayData();
      printData();
    }

    void switchLight(){
      if(C > MAX_TEMPERATURE){
        light->turn_off();
      }
      else if(C < MIN_TEMPERATURE){
        light->turn_on();
      }
    }

    void saveMaxTemp(){
      if(C > maxc){
        maxc = C;
      }
      else if (C < minc){
        minc = C;
      };
    }

    void rotateEggs(){
      if(timeToRotate()){
        servo->move(0);
      }else{
        servo->move(180);
      }
    }

    bool timeToRotate(){
      tmElements_t tm = myClock->read();
      return (tm.Second % 10) > 4;//(tm.Hour+4) % 24 < 12;
    }

    void displayData(){
      display->clearDisplay();
      display->setCursor(0, 0);  
      display->setTextSize(3);
      display->println(String(C));

      tmElements_t tm = myClock->read();
      String text = print2digits(tm.Hour) + ':' + print2digits(tm.Minute) + ':' + print2digits(tm.Second);
        
      display->setTextSize(1);
      display->println(text);
      display->display();
    }
    
    void printData(){
      Serial.print(power_on_time);
      Serial.print(" ");
      Serial.print(C);
      Serial.print(" ");
      Serial.print(thermometer->get_R());
      Serial.print(" ");
      Serial.print(maxc);
      Serial.print(" ");
      Serial.print(minc);
      Serial.print(" ");
      Serial.print(MAX_TEMPERATURE);
      Serial.print(" ");
      Serial.print(MIN_TEMPERATURE);
      Serial.print(" ");
      if (light->get_state()){
          Serial.print("ON");
      }
      else{
          Serial.print("OFF");
      }
      Serial.print(" ");
      Serial.println(Serial.parseFloat());
    }
};



Thermometer * thermo;
Light * light;
MyServo * servo;
MyClock * myClock;
Adafruit_SSD1306 * display;

Controller * controller;

void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  errorBlinking();
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  
  thermo = new Thermometer(analogPin);
  light = new Light(relaypin);
  servo = new MyServo(9, 0, 0.5);
  myClock = new MyClock();
  display = new Adafruit_SSD1306(128, 32, &Wire, 4);
  controller = new MMController(thermo, light, servo, myClock, display);
  
  controller->setup();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  controller->process();
  delay(1000); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
