//
// Created by daniel on 12/14/15.
//

#include "MotorController.h"
#include "Arduino.h"

//TODO: Rewrite so constants is takjen by constructor

#define degreerange 180 // The range of degrees that the servo can move
#define potirange 1024 // The range of the readings from the poti

#define potimin 15 // The minimal reading that we can get from the poti
#define maxreading 1023 // The maximal reading that we can get from the poti
#define potimax potirange - maxreading // The values that the poti will never enter


#define realpotirange abs(potirange-potimax) - potimin // The range of degrees that the servo can move

#define multiplier ((0.00 + degreerange) / (0.00 + realpotirange)) // The range of degrees that the servo can move




MotorController::MotorController(int potiport, int motorpin1, int motorpin2, int motorpvmpin, float* initialtargetsize) : _motor(
        motorpin1, motorpin2, motorpvmpin) {

    _targetsize = initialtargetsize;
    _potiPort = potiport;
    _clipping = false;
    _clippingvalue = 10;

    _motor.setSpeed(0); //makes motor choose minimal speec


}

void MotorController::sendSubTarget(float degree) {

    if(degree > degreerange) degree = degreerange; //ensures that we cannot get out of range no matter of clipping

    if (_clipping) {
        degree = clipDegree(degree); // Clips the degree
    }

    _subTargetDegree = degree;

    moveToNextSubTarget();

}


void MotorController::update() {

    _readDegree = degreeFromPotiReading();

    _error = _subTargetDegree - _readDegree;

}

void MotorController::moveToNextSubTarget() {

    _ready = false; // We are in the process of a move and is not ready to recieve further instructions

    //TODO: Overvej om den skal skifte tidligere fx ved targetsize + 1

    update();

    while (abs(getError()) > *_targetsize) { // Runs until we reach the target thereby ensuring that the timing is right

        update();

        _motor.move(_error, *_targetsize);

    }

    _ready = true;

}






float MotorController::clipDegree(float degree) {

    if (degree < _clippingvalue) degree = _clippingvalue;

    if (degree >= degreerange - _clippingvalue) degree = degreerange - _clippingvalue;

    return degree;

}

void MotorController::setTargetDegree(int value) {

    _subTargetDegree = value;

}

int MotorController::degreeFromPotiReading() {

    int value = readPoti();

    value -= potimin;

    return convertToDegree(value);


}

int MotorController::readPoti() {

    return analogRead(_potiPort);

}

double MotorController::convertToDegree(int reading) {

    //return (reading * multiplier) - (degreerange / 2);

    return (reading * multiplier);

}




