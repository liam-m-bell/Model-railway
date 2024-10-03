//#include <Servo.h>
#include <VarSpeedServo.h>
#include "turnout.h"

turnout::turnout()
{
    id_ = 0;
    LEDPin_ = 0;
}

turnout::turnout(int id, lever& l, int servo, int led)
{
    id_ = id;
    LEDPin_ = led;
    plever_ = l;
    servoPin_ = servo;
}

void turnout::saveToEEPROM()
{
    EEPROM.update(id_, bThrown_);
}

void turnout::readFromEEPROM()
{
    bool state = EEPROM.read(id_);
    set(state);
}

void turnout::writePins()
{
    digitalWrite(LEDPin_, bThrown_);

    // Servo
    if (bThrown_)
    {
        servo_.write(90, 20);
    }
    else
    {
        servo_.write(0, 20);
    }
}

void turnout::update()
{
    writePins();
    saveToEEPROM();
}

void turnout::checkLever()
{
    if (plever_.detectChange())
    {
        toggle();
    }
}

void turnout::checkSerial()
{
    /*
    if (Serial.available() > 0)
    {
        if (Serial.read() == number)
        {
            toggle();
        }
    }
    */
    
}

void turnout::setup()
{
    pinMode(LEDPin_, OUTPUT);
    servo_.attach(servoPin_);
    plever_.setup();
    readFromEEPROM();
}

void turnout::set(bool state)
{
    bThrown_ = state;
    update();
}

void turnout::toggle()
{
    bThrown_ = !bThrown_;
    update();
    Serial.print("Turnout ");
    Serial.print(id_);
    Serial.println(" toggled");
}

void turnout::centre()
{
    servo_.write(45, 100);
}

void turnout::checkInputs()
{
    checkLever();
}

bool turnout::getState()
{
  return bThrown_;
}
