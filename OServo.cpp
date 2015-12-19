//
// Created by daniel on 12/14/15.
//

#include "OServo.h"
#include "Motor.h"
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
#define targetsize 1


float readdegree;
int targetdegree;
float error;


int potiPort = 0;


//Makes motor with correct pins
Motor motor(3, 4, 9);

bool clipping = false;

OServo::OServo() {

    //TODO: Should take port as a parameter
    motor.setSpeed(255);

}

void OServo::update() {

    readDegree = degreeFromPotiReading();

    error = targetdegree - readDegree;

}

void OServo::write(float degree) {

    degree = clipDegree(degree); // Clips the degree


    targetdegree = degree;

    update();


    motor.move(error, targetsize);


}

float OServo::clipDegree(float degree) {

    if(!clipping) return degree; // If clipping are off do nothing

    if(degree < clippingvalue) degree = clippingvalue;

    if(degree >= degreerange - clippingvalue) degree = degreerange - clippingvalue;

    return degree;

}

void OServo::setTargetDegree(int value) {

    targetdegree = value;

}

int OServo::degreeFromPotiReading() {

    int value = readPoti();

    value -= potimin;

    return convertToDegree(value);


}

int OServo::readPoti(){

    return analogRead(potiPort);

}

double OServo::convertToDegree(int reading) {

    //return (reading * multiplier) - (degreerange / 2);

    return (reading * multiplier);

}

float OServo::getError() {

    return error;
}

float OServo::getPosition() {

    return readDegree;

}

int OServo::getTargetDegree() {


    return targetdegree;

}




