//
// Created by daniel on 12/19/15.
//

#ifndef PID_OSERVO_H
#define PID_OSERVO_H


#include <Arduino.h>
#include "MotorController.h"

class OServo {

    float _threshold;

    //Animations
    float _pos;
    float _iterations;

    int _degreerange;

    float _actualPosition;



    MotorController _motorController;
public:
    OServo(int potiport, int motorPin1, int motorPin2, int motorPVMpin);

    void write(float degree);
private:
    void animateOut(float degree);

    void animateIn(float degree);
};


#endif //PID_OSERVO_H
