#include <Arduino.h>
#include "servopid.h"

#define enablePin 9 // pin 1 on L293D

PIDServo servo;
unsigned long updateLastTime = 0;


//This is actually master!!
void setup()
{

    servo.begin();
    digitalWrite(enablePin, HIGH);
}



void loop()
{
    if(millis() - updateLastTime > 20)
    {
        updateLastTime = millis();
        servo.update();
    }
}