//
// Created by daniel on 12/14/15.
//
#include "Motor.h"


#ifndef PID_MotorController_H
#define PID_MotorController_H


class MotorController {



    float readDegree;
    float targetDegree;
    float error;
    int potiPort;
    bool clipping;

    Motor motor;


public:

    MotorController(int potiport, int motorpin1, int motorpin2, int motorpvmpin);

    int degreeFromPotiReading();

    void update();

    double convertToDegree(int reading);

    void setTargetDegree(int value);

    void sendSubTarget(float degree);

    int readPoti();


private:


    float clipDegree(float degree);


public:
    void setClipping(bool clipping) {
        MotorController::clipping = clipping;
    }

    float getTargetDegree() const {
        return targetDegree;
    }

    float getError() const {
        return error;
    }

    float getReadDegree() const {
        return readDegree;
    }
};


#endif //PID_MotorController_H
