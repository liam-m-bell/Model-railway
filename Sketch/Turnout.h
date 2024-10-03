#ifndef turnout_h
#define turnout_h

#include <Arduino.h>
#include <EEPROM.h>
//#include <Servo.h>
#include <VarSpeedServo.h>
#include "lever.h"

class turnout
{
    private:
        int id_;
        int LEDPin_;
        int servoPin_;
        bool bThrown_;
        lever plever_;
        VarSpeedServo servo_;

        void saveToEEPROM();
        void readFromEEPROM();

        void writePins();

        void checkLever();
        void checkSerial();


    public:
        turnout();
        turnout(int id, lever& l, int servo, int led);

        void setup();

        void set(bool state);
        void toggle();

        void centre();

        void update();

        void checkInputs();

        bool getState();
};
#endif
