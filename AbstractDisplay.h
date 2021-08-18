#ifndef ABSTRACT_DISPLAY

#define ABSTRACT_DISPLAY
class AbstractDisplay{
    public:
        virtual void displayData(String temperature, String date) = 0;
        virtual void displayError(String message) = 0;
};
#endif