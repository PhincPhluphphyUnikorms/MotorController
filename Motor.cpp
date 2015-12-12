//
// Created by daniel on 12/11/15.
//

#include "Motor.h"
#include "Arduino.h"

#define motorlimit 170 //The smallest pwm signal it takes to make the motor move


int _motor1Pin1;
int _motor1Pin2;
int _enablePin;


Motor::Motor(int pin1, int pin2, int enablepin) {

    _motor1Pin1 = pin1;
    _motor1Pin2 = pin2;
    //analogWrite(enablepin, motorlimit);
    _enablePin = enablepin;



}

void Motor::clockwise() {

    digitalWrite(_motor1Pin1, LOW);
    digitalWrite(_motor1Pin2, HIGH);


}


void Motor::counterClockwise() {

    digitalWrite(_motor1Pin1, HIGH);
    digitalWrite(_motor1Pin2, LOW);

}

void Motor::stop() {
    digitalWrite(_motor1Pin1, LOW);
    digitalWrite(_motor1Pin2, LOW);

}

void Motor::move(double degrees, int threshold) {


    if(degrees <= threshold && -threshold <= degrees) {

        stop();

    } else if(degrees > 0) {

        counterClockwise();

    } else {

        clockwise();


    }


}

void Motor::setSpeed(int speed) {

    if(speed > 255) speed = 255;
    else if(speed < motorlimit) speed = motorlimit;

    analogWrite(_enablePin, speed);

}
