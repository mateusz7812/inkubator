
#include <Adafruit_SSD1306.h>
#include "Reporter.h"
#include "AbstractDisplay.h"

class Display : public AbstractDisplay {
    private:
        Adafruit_SSD1306 * display;
        Reporter * reporter;
    public:
        Display(Reporter * reporter);
        void displayData(char temperature[], char additional[], bool light_state) override;
        void displayError(char message[]) override;        
};