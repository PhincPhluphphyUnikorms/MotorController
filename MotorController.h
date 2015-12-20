//
// Created by daniel on 12/14/15.
//
#include "Motor.h"


#ifndef PID_MotorController_H
#define PID_MotorController_H


class MotorController {


    float _readDegree;
    float _subTargetDegree;
    float _error;
    int _potiPort;
    bool _clipping;
    float* _targetsize;
    float _clippingvalue;
    bool _ready;

    float _multiplier;
    int* _degreerange;


    Motor _motor;

public:

    MotorController(int potiport, int motorpin1, int motorpin2, int motorpvmpin, int *degreerange,
                    float *initialtargetsize);

    int degreeFromPotiReading();

    void update();

    double convertToDegree(int reading);

    void setTargetDegree(int value);

    void sendSubTarget(float degree);


    int readPoti();


private:
    float clipDegree(float degree);


    void moveToNextSubTarget();

public:

    void setClipping(bool clipping) {
        MotorController::_clipping = clipping;
    }

    float getTargetDegree() const {
        return _subTargetDegree;
    }

    float getError() const {
        return _error;
    }

    float getReadDegree() const {
        return _readDegree;
    }

    float getclippingvalue() const {
        return _clippingvalue;
    }

    void setclippingvalue(float _clippingvalue) {
        MotorController::_clippingvalue = _clippingvalue;
    }
};



#endif //PID_MotorController_H
