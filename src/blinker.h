#ifndef BLINKER_H
#define BLINKER_H

const unsigned long DEFAULT_BLINK_INTERVAL = 30;

class Blinker
{    
    unsigned long timer;
    unsigned long blinkInterval;
    bool visible; 
    public:
        Blinker();
        ~Blinker();
        void loop();
        unsigned long getTimer();
        void setBlinkInterval(unsigned long blinkInterval);
        unsigned long getBlinkInterval();
        bool isVisible();       
};

#endif // BLINKER_H