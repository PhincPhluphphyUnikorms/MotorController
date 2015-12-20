//
// Created by daniel on 12/19/15.
//

#ifndef PID_OSERVO_H
#define PID_OSERVO_H


#include <Arduino.h>
#include "MotorController.h"

class OServo {

    float _threshold;

    float _iterations;


    //Animations
    float _pos;

    int _degreerange;

    float _actualPosition;

    float _oldSuperError;

    float _superError;

    MotorController _motorController;


public:
    OServo(int potiport, int motorPin1, int motorPin2, int motorPVMpin);
    void write(float degree);


private:


    bool sameSign(int x, int y);

    bool _firstrun;

    void alwaysEaseOutOnFIrstRun();

    void alwaysEaseOutOnFirstRun(int degree);

    void animateIn(float error);

    void animateOut(float error);
};


#endif //PID_OSERVO_H
