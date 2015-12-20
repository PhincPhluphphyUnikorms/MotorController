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


}


void loop() {

    servo.write(180);

}

