#include "lever.h"

lever::lever()
{
    pin_ = 0;
    bPowered_ = false;
    readDelay_ = 0;
}

lever::lever(int pin)
{
    pin_ = pin;
    bPowered_ = false;
    readDelay_ = 0;
}

void lever::setup()
{
    pinMode(pin_, INPUT_PULLUP);
    bPowered_ = digitalRead(pin_);
}

void lever::setReadDelay(int delay)
{
    readDelay_ = delay;
}

bool lever::detectChange()
{
    bool change = false;
    bool reading = digitalRead(pin_);
    change = (reading != bPowered_);
    bPowered_ = reading;
    return change;
}