//
// Created by daniel on 12/11/15.
//

#include "Motor.h"
#include "Arduino.h"


int _motor1Pin1;
int _motor1Pin2;
int enablepin;


Motor::Motor(int pin1, int pin2, int enablepin) {

    _motor1Pin1 = pin1;
    _motor1Pin2 = pin2;

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
