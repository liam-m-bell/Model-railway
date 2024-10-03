/*
 Name:		Sketch.ino
 Created:	3/29/2020 2:18:03 PM
 Author:	Liam
*/
#include <LiquidCrystal.h>
#include "HardwareSerial.h"
#include "lever.h"
#include "turnout.h"

const int setupLever = 52;
bool bSetup = false;

const int turnoutCount = 10;
const int turnoutStartPin = 2;

/*
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

byte thrownChar[] = {
  B10010,
  B10010,
  B00010,
  B00100,
  B01000,
  B10000,
  B10000,
  B10000
};

byte closedChar[] = {
  B10010,
  B10010,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};
*/

lever levers[10] = {
    {34},
    {36},
    {38},
    {40},
    {43},
    {39},
    {42},
    {37},
    {41},
    {35}
};

turnout turnouts[10] = {
    {0, levers[0], 0 + turnoutStartPin, 24},
    {1, levers[1], 1 + turnoutStartPin, 26},
    {2, levers[2], 2 + turnoutStartPin, 28},
    {3, levers[3], 3 + turnoutStartPin, 30},
    {4, levers[4], 4 + turnoutStartPin, 25},
    {5, levers[5], 5 + turnoutStartPin, 31},
    {6, levers[6], 6 + turnoutStartPin, 22},
    {7, levers[7], 7 + turnoutStartPin, 27},
    {8, levers[8], 8 + turnoutStartPin, 29},
    {9, levers[9], 9 + turnoutStartPin, 23},
};

// the setup function runs once when you press reset or power the board
void setup()
{
    pinMode(setupLever, INPUT_PULLUP);

    Serial.begin(9600);

    for (int i = 0; i < turnoutCount; i++)
    { 
        turnouts[i].setup();
    }

    Serial.println("setup complete");

    /*
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("0 1 2 3 4 5");

    lcd.createChar(0, thrownChar);
    lcd.createChar(1, closedChar);
    */
}

// loop function runs over and over again until power down or reset
void loop()
{
    if (!digitalRead(setupLever))
    {
        bSetup = true;

        for (int i = 0; i < turnoutCount; i++)
        {
            turnouts[i].centre();
        }
    }
    else
    {
        if (bSetup = true)
        {
            bSetup = false;

            for (int i = 0; i < turnoutCount; i++)
            {
                turnouts[i].update();
            }
        }
        
        update();
    }    
}

void update()
{
    if (Serial.available() > 0)
    {
        int i = atoi(Serial.readString().c_str());
        turnouts[i].toggle();       
    }

    for (int i = 0; i < turnoutCount; i++)
    {
        turnouts[i].checkInputs();

        /*
        lcd.setCursor(2 * i, 1);
        if (turnouts[i].getState())
        {
          
          lcd.write(byte(0));
        }
        else
        {
          lcd.write(byte(1));
        }
        */
    }
}
