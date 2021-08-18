
#include <Adafruit_SSD1306.h>
#include "Reporter.h"
#include "AbstractDisplay.h"

class Display : public AbstractDisplay {
    private:
        Adafruit_SSD1306 * display;
        Reporter * reporter;
    public:
        Display(Reporter * reporter);
        void displayData(String temperature, String date) override;
        void displayError(String message) override;        
};