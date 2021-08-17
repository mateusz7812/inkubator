class ErrorReporter {
    private:
        Stream * stream;
        int pin;
        Display * display;
    public:
        void setPin(int pin);
        void setStream(Stream * stream);
        void setDisplay(Display * display);
        void reportError(string message);
};