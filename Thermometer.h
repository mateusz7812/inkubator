
class Thermometer {
  private:
    int pin;
    int raw = 0;
    double Vin = 4.44;
    double Vout = 0;
    double R1 = 10000;
    double R2 = 0;
    double buffer = 0;
    double R = 0;
  public:
    Thermometer(int analog_pin){
      pin = analog_pin;
    }

    double get_R();

    double measure();
  };