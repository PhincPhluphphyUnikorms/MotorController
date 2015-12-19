#include <Arduino.h>
#include "Motor.h"
#include "OServo.h"
#include <PID_v1.h>
#include "easing.h"

float servoPos, pos;
float iterations = 1000; // Iterationer pr animation


double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp = 0.49, Ki = 0.01, Kd = 0;
PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


unsigned long updateLastTime = 0;

OServo servo;

void wait();


void setup() {


    pid.SetMode(AUTOMATIC);
    pid.SetOutputLimits(0, 180); // Bør justeres sammen med SetDegrees retur



}


void loop() {


    //updateLastTime = millis() / 1000;

    // pid.Compute();


    //servo.write(Output);

    servo.write(0);

    wait();

    for (pos = 0; pos <= iterations; pos++) {

        servoPos = (180 - 10) * CircularEaseOut(pos / iterations);

        servo.write(servoPos);

        wait();

    }

    wait();


    for (pos = iterations; pos >= 0; pos--) {

        servoPos = (180 - 10 ) * CircularEaseIn(pos / iterations);

        servo.write(servoPos);

        wait();

    }


}


void wait() {


    while (abs(servo.getError()) > 1) {

        servo.write(servoPos);

    }

}


