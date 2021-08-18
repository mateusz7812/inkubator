#include "Display.h"

Display::Display(Reporter * reporter){
    this->reporter = reporter;
    display = new Adafruit_SSD1306(128, 32, &Wire, 4);
    
    if(!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        reporter->reportError(F("SSD1306 allocation failed"));
    }
    
    display->setTextColor(SSD1306_WHITE);
    display->cp437(true); 
}

void Display::displayData(String temperature, String date){
    display->clearDisplay();
    display->setCursor(0, 0);  
    display->setTextSize(3);
    display->println(temperature);

    display->setTextSize(1);
    display->println(date);
    display->display();
}

void Display::displayError(String message){
    display->clearDisplay();
    display->setCursor(0, 0);  
    display->setTextSize(2);
    display->println(message);
    display->display();
}