//
// Created by daniel on 12/14/15.
//

#include "MotorController.h"
#include "Arduino.h"

//TODO: Rewrite so constants is takjen by constructor

#define degreerange 170 // The range of degrees that the servo can move
#define potirange 1024 // The range of the readings from the poti

#define potimin 15 // The minimal reading that we can get from the poti
#define maxreading 1023 // The maximal reading that we can get from the poti
#define potimax potirange - maxreading // The values that the poti will never enter


#define realpotirange abs(potirange-potimax) - potimin // The range of degrees that the servo can move

#define multiplier ((0.00 + degreerange) / (0.00 + realpotirange)) // The range of degrees that the servo can move


#define clippingvalue 10
#define targetsize 5


//Makes motor with correct pins




MotorController::MotorController(int potiport, int motorpin1, int motorpin2, int motorpvmpin) : motor(
        motorpin1, motorpin2, motorpvmpin) {


    potiPort = potiport;
    clipping = false;

    motor.setSpeed(255);


}

void MotorController::sendSubTarget(float degree) {

    if (clipping) {
        degree = clipDegree(degree); // Clips the degree

    }

    targetDegree = degree;


    update();


    motor.move(error, targetsize);


}

void MotorController::update() {

    readDegree = degreeFromPotiReading();

    error = targetDegree - readDegree;

}


float MotorController::clipDegree(float degree) {

    if (degree < clippingvalue) degree = clippingvalue;

    if (degree >= degreerange - clippingvalue) degree = degreerange - clippingvalue;

    return degree;

}

void MotorController::setTargetDegree(int value) {

    targetDegree = value;

}

int MotorController::degreeFromPotiReading() {

    int value = readPoti();

    value -= potimin;

    return convertToDegree(value);


}

int MotorController::readPoti() {

    return analogRead(potiPort);

}

double MotorController::convertToDegree(int reading) {

    //return (reading * multiplier) - (degreerange / 2);

    return (reading * multiplier);

}




