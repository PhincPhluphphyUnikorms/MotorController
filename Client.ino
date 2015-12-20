#include <Arduino.h>
#include "Motor.h"
#include "MotorController.h"
#include <PID_v1.h>
#include "easing.h"
#include "OServo.h"

OServo servo;

void setup() {


}


void loop() {

    servo.write(130);

}

