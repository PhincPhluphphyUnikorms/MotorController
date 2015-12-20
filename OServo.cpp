//
// Created by daniel on 12/19/15.
//

#include "OServo.h"
#include "MotorController.h"
#include <PID_v1/PID_v1.h>
#include "easing.h"


//Specify the links and initial tuning parameters for the PID
double Setpoint, Input, Output;
double Kp = 0.49, Ki = 0.01, Kd = 0;
PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


int targetsize = 5; // the initial value of targetsize

//TODO: Ende oscilation med QuinticEase og ExponentialEase, BackEaseIn
//TODO: Optimer for ElasticEaseOut



OServo::OServo(int potiport, int motorPin1, int motorPin2, int motorPVMpin) :
        _motorController(potiport, motorPin1, motorPin2, motorPVMpin, &_degreerange, &_threshold, &_actualPosition) {


    _threshold = 5;
    _degreerange = 180;
    _firstrun = true;


    //PID
    pid.SetMode(AUTOMATIC);
    pid.SetOutputLimits(0, 180); // Bør justeres sammen med SetDegrees retur

    _iterations = 2000; // Iterationer pr animation


    _motorController.calibrate();

}



void OServo::write(float degree) {

    _motorController.update(); // Makes the motor controller update the values incl the poti reading
    alwaysEaseOutOnFirstRun(degree);


    _oldSuperError = _superError;

    _superError = degree - _actualPosition;


    Serial.print("ACtual POS: ");
    Serial.println(_actualPosition);


    if (sameSign(_oldSuperError, _superError)) {



        Serial.print("IN: ");
        Serial.println(_superError);

        animateIn(_superError);


    } else {

        Serial.print("OUT: ");
        Serial.println(_superError);

        animateOut(_superError);


    }


}

bool OServo::sameSign(int x, int y) {
    return (x >= 0) ^ (y < 0);
}


void OServo::animateIn(float degree) {


    float startpos = _actualPosition;

    for (int pos = 0; pos <= _iterations; pos++) {


        float subtarget = startpos + (degree * ExponentialEaseIn(pos / _iterations));

        _motorController.sendSubTarget(subtarget);


    }

}


void OServo::animateOut(float degree) {


    float startpos = _actualPosition;


    for (int pos = 0; pos <= _iterations; pos++) {

        float subtarget = startpos + (degree * ExponentialEaseOut(pos / _iterations));

        //Input = _servoPos;

        //pid.Compute();

        _motorController.sendSubTarget(subtarget);

    }


}


void OServo::alwaysEaseOutOnFirstRun(int degree) {


    if (_firstrun) { // Ensures that we always get the same sign in the first rum --> We always ease out

        _superError = degree - _actualPosition;

        _firstrun = !_firstrun;
    }


}
