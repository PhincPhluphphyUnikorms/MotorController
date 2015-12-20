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


    enum AnimationType {

        LINEAR, QUADRATIC, CUBIC, QUARTIC, QUINTIC, SINE, CIRCULAR, EXPONENTIAL, ELASTIC, BACK, BOUNCE

    };

    enum EaseDirection {

        EASEIN, EASEOUT, EASEINOUT

    };


    AnimationType _animationType;

    EaseDirection _easeDirection;


    String getColorName(OServo::AnimationType type) {
        String typeName[] = {"Linear", "Quadratic", "Cubic", "Quartic", "Quintic,", "Sine", "Circular", "Exponential",
                             "Elastic,", "Back", "Bounce"};
        return typeName[type];
    }

public:
    OServo(int potiport, int motorPin1, int motorPin2, int motorPVMpin, AnimationType animationtype);

    void write(float degree);


private:


    bool sameSign(int x, int y);

    bool _firstrun;

    void alwaysEaseOutOnFIrstRun();

    void alwaysEaseOutOnFirstRun(int degree);

    void animateIn(float error);

    void animateOut(float error);

    float calculateAnimation(float input);

    float calculateInOut(float input);

    float calculateIn(float input);

    float calculateOut(float input);

    void animate(float degree);

public:
    const AnimationType &get_animationType() const {
        return _animationType;
    }

    void set_animationType(const AnimationType &_animationType) {
        OServo::_animationType = _animationType;
    }

    const EaseDirection &get_easeDirection() const {
        return _easeDirection;
    }

    void set_easeDirection(const EaseDirection &_easeDirection) {
        OServo::_easeDirection = _easeDirection;
    }
};


#endif //PID_OSERVO_H
