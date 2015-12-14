//
// Created by daniel on 12/14/15.
//
#include "Motor.h"


#ifndef PID_OSERVO_H
#define PID_OSERVO_H


class OServo {

public:
    OServo();

    int degreeFromPotiReading();
    void update();
    double convertToDegree(int reading);
    void setTargetDegree(int value);
    void write(float degree);
    float getPosition();
    float getError();
    int getTargetDegree();

private:
    float readDegree;
    int targetdegree;
    float error;


};


#endif //PID_OSERVO_H
