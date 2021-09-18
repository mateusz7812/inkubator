#include "Display.h"

Display::Display(Reporter *reporter)
{
    this->reporter = reporter;
    display = new Adafruit_SSD1306(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, DISPLAY_PIN);

    if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        reporter->reportError("SSD1306 allocation failed");
    }

    display->setTextColor(SSD1306_WHITE);
    display->cp437(true);
}

void Display::displayData(char temperature[], char additional[], bool light_state)
{
    display->clearDisplay();
    display->setCursor(0, 0);
    display->setTextSize(3);
    display->println(temperature);

    display->setTextSize(1);
    display->println(additional);

    display->setCursor(90, 2);
    display->setTextSize(2);
    if (light_state)
        display->print("ON");
    else
        display->print("OFF");

    display->display();
}

void Display::displayError(char message[])
{
    display->clearDisplay();
    display->setCursor(0, 0);
    display->setTextSize(2);
    display->println(message);
    display->display();
}