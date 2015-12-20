//
// Created by daniel on 12/19/15.
//

#include "OServo.h"
#include "MotorController.h"
#include <PID_v1/PID_v1.h>
#include "easing.h"


//Animations
float servoPos, pos;
float iterations = 1000; // Iterationer pr animation


MotorController motorController(0, 3, 4, 9);


//Specify the links and initial tuning parameters for the PID
double Setpoint, Input, Output;
double Kp = 0.49, Ki = 0.01, Kd = 0;
PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);




//TODO: Ende oscilation med QuinticEase og ExponentialEase, BackEaseIn
//TODO: Optimer for ElasticEaseOut



OServo::OServo() {

    pid.SetMode(AUTOMATIC);
    pid.SetOutputLimits(0, 180); // Bør justeres sammen med SetDegrees retur

}


void OServo::write(float degree) {

    boolean pidOn = true;

    servoPos = degree;

    motorController.sendSubTarget(degree);
    wait();


}




void OServo::animateIn(float degree) {


    for (pos = iterations; pos >= 0; pos--) {

        servoPos = (180 - 10) * ExponentialEaseIn(pos / iterations);

        motorController.sendSubTarget(servoPos);

        wait();

    }


}

void OServo::animateOut(float degree) {

    for (pos = 0; pos <= iterations; pos++) {

        servoPos = (180 - 10) * ExponentialEaseOut(pos / iterations);

        Input = servoPos;

        pid.Compute();

        motorController.sendSubTarget(Output);

        wait();

    }


}

void OServo::wait() {

    ready = false;

    while (abs(motorController.getError()) > 5) {

        motorController.sendSubTarget(servoPos);



    }

    ready = true;

}

