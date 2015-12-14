//
// Created by daniel on 12/14/15.
//

#include "OServo.h"
#include "Motor.h"
#include "Arduino.h"

//TODO: Rewrite so constants is takjen by constructor

#define degreerange 170 // The range of degrees that the servo can move
#define potirange 1024 // The range of the readings from the poti

#define potimin 43 // The minimal reading that we can get from the poti
#define maxreading 542 // The maximal reading that we can get from the poti
#define potimax potirange - maxreading // The values that the poti will never enter


#define realpotirange abs(potirange-potimax) - potimin // The range of degrees that the servo can move

#define multiplier ((0.00 + degreerange) / (0.00 + realpotirange)) // The range of degrees that the servo can move



float readdegree;
int targetdegree;
float error;


//Makes motor with correct pins
Motor motor(3, 4, 9);

OServo::OServo() {

    //TODO: Should take port as a parameter
    motor.setSpeed(255);

}

void OServo::update() {

    readdegree = degreeFromPotiReading();

    error = targetdegree - readdegree;

}

void OServo::write(float degree) {


    targetdegree = degree;

    update();


    motor.move(degree, 2);


}

void OServo::setTargetDegree(int value) {

    targetdegree = value;

}

int OServo::degreeFromPotiReading() {

    int value = analogRead(0);

    value -= potimin;

    return convertToDegree(value);


}

double OServo::convertToDegree(int reading) {

    //return (reading * multiplier) - (degreerange / 2);

    return (reading * multiplier);

}

float OServo::getError() {

    return error;
}

float OServo::getPosition() {

    return readdegree;

}

int OServo::getTargetdegree() {


    return targetdegree;

}


