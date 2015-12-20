//
// Created by daniel on 12/14/15.
//

#include "MotorController.h"
#include "Arduino.h"

//TODO: Rewrite so constants is taken by constructor maybe the rest (poti related stuff) iss ok to keep here

#define potirange 1024 // The range of the readings from the poti

#define potimin 15 // The minimal reading that we can get from the poti
#define maxreading 1023 // The maximal reading that we can get from the poti
#define potimax potirange - maxreading // The values that the poti will never enter

#define realpotirange abs(potirange-potimax) - potimin // The range of degrees that the servo can move

MotorController::MotorController(int potiport, int motorpin1, int motorpin2, int motorpvmpin, int * degreerange,
                                 float * initialtargetsize, float * currentposition) : _motor(motorpin1, motorpin2, motorpvmpin) {


    _currentPosition = currentposition;

    _degreerange = degreerange; // The range of degrees that the servo can move
    _targetsize = initialtargetsize;
    _potiPort = potiport;
    _clipping = true;
    _clippingvalue = 2;



}

/**
 * Initialise values so other classes have them
 */
void MotorController::calibrate(){

    _multiplier = ((0.00 + *_degreerange) / (0.00 + realpotirange)); // The range of degrees that the servo can move

    _motor.setSpeed(255); //makes motor choose minimal speec



}

/**
 * Takes the absolute target and send it to the motor
 */
void MotorController::sendSubTarget(float degree) {

    if (degree > *_degreerange) degree = *_degreerange; //ensures that we cannot get out of range no matter of clipping

    if (_clipping) {
        degree = clipDegree(degree); // Clips the degree
    }

    _subTargetDegree = degree;

    moveToNextSubTarget();

}


/**
 * Update reading from poti and recalculate error
 */
void MotorController::update() {

    *_currentPosition = degreeFromPotiReading();

    _error = _subTargetDegree - *_currentPosition;

}


/**
 * Pass the next target to the motor and wait until we reach it before returning control
 */
void MotorController::moveToNextSubTarget() {

    _ready = false; // We are in the process of a move and is not ready to recieve further instructions

    //TODO: Overvej om den skal skifte tidligere fx ved targetsize + 1

    update();

    while (abs(getError()) > *_targetsize) { // Runs until we reach the target thereby ensuring that the timing is right

        update();

        _motor.move(_error, *_targetsize);

    }

    _ready = true; // move done we are ready again

}

/**
 * CLippes the top and bottum of a curve.
 */
float MotorController::clipDegree(float degree) {

    if (degree < _clippingvalue) degree = _clippingvalue;

    if (degree >= *_degreerange - _clippingvalue) degree = *_degreerange - _clippingvalue;

    return degree;

}

/**
 * Sets next target
 */
void MotorController::setTargetDegree(int value) {

    _subTargetDegree = value;

}


/**
 * Calculates the current prosition in degrees based on reading from poti
 */
int MotorController::degreeFromPotiReading() {

    int value = readPoti();

    value -= potimin;

    return convertToDegree(value);


}

/**
 * Reads the poti
 */
int MotorController::readPoti() {

    return analogRead(_potiPort);

}

/**
 * Converts analogreading to degree
 */
double MotorController::convertToDegree(int reading) {

    //return (reading * _multiplier) - (_degreerange / 2);

    return (reading * _multiplier);

}




