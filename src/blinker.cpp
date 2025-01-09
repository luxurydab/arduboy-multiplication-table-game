#include "blinker.h"

Blinker::Blinker()
{
    this->timer = 0;
    this->visible = true; 
    this->setBlinkInterval(DEFAULT_BLINK_INTERVAL);
}

Blinker::~Blinker()
{
}

void Blinker::loop()
{
    if(this->getTimer() > this->getBlinkInterval()){
        this->timer = 0;
        if(this->isVisible() == true){
            this->visible = false;
        }else{
            this->visible = true;
        }
    }
    this->timer++;  
}

unsigned long Blinker::getTimer()
{
    return this->timer;
}

bool Blinker::isVisible()
{
    return this->visible;
}

void Blinker::setBlinkInterval(unsigned long blinkInterval)
{
    this->blinkInterval = blinkInterval;
}

unsigned long Blinker::getBlinkInterval()
{
    return this->blinkInterval;
}
