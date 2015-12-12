//
// Created by daniel on 12/11/15.
//

#ifndef PID_MOTOR_H
#define PID_MOTOR_H


class Motor {

public:
    Motor(int pin1, int pin2, int enablepin);
    void stop();
    void clockwise();
    void counterClockwise();
    void move(double degrees, int threshold);

private:
    int _motor1Pin1;
    int _motor1Pin2;
    int enablepin;

};


#endif //PID_MOTOR_H
