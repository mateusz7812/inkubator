
class MMController: public Controller{
  private:
    double maxc = 0;
    double minc = 40;
    double temp;
    String power_on_time;
  public:
    MMController(Thermometer* t, Light* l, MyServo* s, MyClock* c, AbstractDisplay* d, Reporter* r, SerialManager* m): Controller(t, l, s, c, d, r, m)
    {  
      tmElements_t tm = myClock->read();
      String text = text2digits(tm.Hour) + ':' + text2digits(tm.Minute) + ':' + text2digits(tm.Second) + " " + tm.Day + "/" + tm.Month + "/" + tmYearToCalendar(tm.Year);
      power_on_time = text;
      servo->move(1);
    }
    
    String text2digits(int number) {
      String n = String(number);
      if (number >= 0 && number < 10)
        n = String('0') + n;
      return n;
    }
    
    virtual void setup(){
      delay(1000); 
      Serial.print("Power on!\n");
      
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

      tmElements_t tm = myClock->read();
      String text = text2digits(tm.Hour) + ':' + text2digits(tm.Minute) + ':' + text2digits(tm.Second);

      saveMaxTemp();
      switchLight();
      rotateEggs();
      display->displayData(String(C), text);
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
    
    void printData(){
        double resistance = thermometer->get_R();
        String str = power_on_time + " " + C + " " + resistance + " " + maxc + " " + minc + " " + MAX_TEMPERATURE + " " + MIN_TEMPERATURE + " ";
        if (light->get_state())
            str += "ON ";
        else
            str += "OFF ";
        str += String(serial->readFloat()) + "\n";
        reporter->reportInfo(str);
    }
};
