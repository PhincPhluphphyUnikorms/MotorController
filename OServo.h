//
// Created by daniel on 12/19/15.
//

#ifndef PID_OSERVO_H
#define PID_OSERVO_H


#include <Arduino.h>

class OServo {

    bool ready;


public:
    OServo();
    void write(float degree);


private:
    void wait();
    void animateOut(float degree);
    void animateIn(float degree);

public:
    boolean isReady() const {
        return ready;
    }
};


#endif //PID_OSERVO_H
