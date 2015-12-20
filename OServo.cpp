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



OServo::OServo(int potiport, int motorPin1, int motorPin2, int motorPVMpin, AnimationType animationtype) :
        _motorController(potiport, motorPin1, motorPin2, motorPVMpin, &_degreerange, &_threshold, &_actualPosition) {

    _animationType = animationtype;
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

    //TODO: Find out how we can know that it is last and calculate out there


    if (sameSign(_oldSuperError, _superError)) {

        _easeDirection = EASEIN;

    } else {

        _easeDirection = EASEINOUT;


    }

    animate(_superError);




}

bool OServo::sameSign(int x, int y) {
    return (x >= 0) ^ (y < 0);
}


void OServo::animate(float degree) {

    float startpos = _actualPosition;

    for (int pos = 0; pos <= _iterations; pos++) {


        float subtarget = startpos + (degree * calculateAnimation(pos / _iterations));

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


/******** ANIMATION SWITCHES *********/

AHFloat OServo::calculateAnimation(float input) {

    switch (_easeDirection) {

        case EASEIN:
            return calculateIn(input);
        case EASEOUT:
            return  calculateOut(input);
        case EASEINOUT:
            return calculateInOut(input);
    }

}



AHFloat OServo::calculateOut(float input) {

    switch (_animationType) {
        case  QUADRATIC:
            return QuadraticEaseOut(input);
        case  CUBIC:
            return CubicEaseOut(input);
        case  QUARTIC:
            return QuarticEaseOut(input);
        case  QUINTIC:
            return QuarticEaseOut(input);
        case  SINE:
            return SineEaseOut(input);
        case  CIRCULAR:
            return CircularEaseOut(input);
        case  EXPONENTIAL:
            return ExponentialEaseOut(input);
        case  ELASTIC:
            return ElasticEaseOut(input);
        case  BACK:
            return BackEaseOut(input);
        case  BOUNCE:
            return BounceEaseOut(input);
        default:
            return LinearInterpolation(input);

    }


}

AHFloat OServo::calculateInOut(float input) {

    switch (_animationType) {
        case  QUADRATIC:
            return QuadraticEaseInOut(input);
        case  CUBIC:
            return CubicEaseInOut(input);
        case  QUARTIC:
            return QuarticEaseInOut(input);
        case  QUINTIC:
            return QuarticEaseInOut(input);
        case  SINE:
            return SineEaseInOut(input);
        case  CIRCULAR:
            return CircularEaseInOut(input);
        case  EXPONENTIAL:
            return ExponentialEaseInOut(input);
        case  ELASTIC:
            return ElasticEaseInOut(input);
        case  BACK:
            return BackEaseInOut(input);
        case  BOUNCE:
            return BounceEaseInOut(input);
        default:
            return LinearInterpolation(input);

    }

}



AHFloat OServo::calculateIn(float input) {

    switch (_animationType) {
        case  QUADRATIC:
            return QuadraticEaseIn(input);
        case  CUBIC:
            return CubicEaseIn(input);
        case  QUARTIC:
            return QuarticEaseIn(input);
        case  QUINTIC:
            return QuarticEaseIn(input);
        case  SINE:
            return SineEaseIn(input);
        case  CIRCULAR:
            return CircularEaseIn(input);
        case  EXPONENTIAL:
            return ExponentialEaseIn(input);
        case  ELASTIC:
            return ElasticEaseIn(input);
        case  BACK:
            return BackEaseIn(input);
        case  BOUNCE:
            return BounceEaseIn(input);
        default:
            return LinearInterpolation(input);

    }


}


