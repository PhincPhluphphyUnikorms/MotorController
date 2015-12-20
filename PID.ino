/******************************************************************************
 * @DW
 * This file is named PID because of the arduino build system but i reality acts as a client
 *
 ******************************************************************************/
#include <Arduino.h>
#include "Motor.h"
#include "MotorController.h"
#include <PID_v1.h>
#include "easing.h"
#include "OServo.h"


int potiport = 0;
int motorPin1 = 3;
int motorPin2 = 4;
int motorPVMpin = 9;

OServo servo(potiport, motorPin1, motorPin2, motorPVMpin);

void setup() {


    Serial.begin(9600);

}


void loop() {

    servo.write(0);

    delay(2000);

    servo.write(70);

    delay(2000);

    servo.write(180);




    // Stop
    while(true) {}


}

