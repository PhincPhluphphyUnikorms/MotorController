//
// Created by daniel on 12/19/15.
//

#include "OServo.h"
#include "MotorController.h"
#include <PID_v1/PID_v1.h>
#include "easing.h"


MotorController _motorController();


//Specify the links and initial tuning parameters for the PID
double Setpoint, Input, Output;
double Kp = 0.49, Ki = 0.01, Kd = 0;
PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


int targetsize = 5; // the initial value of targetsize

//TODO: Ende oscilation med QuinticEase og ExponentialEase, BackEaseIn
//TODO: Optimer for ElasticEaseOut



OServo::OServo(int potiport, int motorPin1, int motorPin2, int motorPVMpin) : _motorController(potiport, motorPin1,
                                                                                               motorPin2, motorPVMpin,
                                                                                               &_degreerange,
                                                                                               &_threshold) {

    _threshold = 5;
    _degreerange = 180;

    //PID
    pid.SetMode(AUTOMATIC);
    pid.SetOutputLimits(0, 180); // Bør justeres sammen med SetDegrees retur

    _iterations = 2000; // Iterationer pr animation


    _motorController.calibrate();

}


void OServo::write(float degree) {

    boolean pidOn = true;

    _servoPos = degree;


    _motorController.sendSubTarget(degree);


}


void OServo::animateIn(float degree) {


    for (_pos = _iterations; _pos >= 0; _pos--) {

        _servoPos = (180 - 10) * ExponentialEaseIn(_pos / _iterations);

        _motorController.sendSubTarget(_servoPos);

    }


}

void OServo::animateOut(float degree) {

    for (_pos = 0; _pos <= _iterations; _pos++) {

        _servoPos = (180 - 10) * ExponentialEaseOut(_pos / _iterations);

        Input = _servoPos;

        pid.Compute();

        _motorController.sendSubTarget(Output);

    }


}

