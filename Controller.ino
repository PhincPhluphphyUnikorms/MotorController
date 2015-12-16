#include <Arduino.h>
#include "Motor.h"
#include "OServo.h"
#include <PID_v1.h>
#include "easing.h"

float servoPos, pos;
float iterations = 200; // Iterationer pr animation


double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp = 0.49, Ki = 0.01, Kd = 0;
PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


unsigned long updateLastTime = 0;

OServo servo;


void setup() {

    Serial.begin(9600);


    pid.SetMode(AUTOMATIC);
    pid.SetOutputLimits(0, 180); // Bør justeres sammen med SetDegrees retur

    Serial.begin(9600);


}


void loop() {


    updateLastTime = millis() / 1000;

   // pid.Compute();


    //servo.write(Output);


    servo.write(0);

    delay(4000);

    for (pos = 0; pos <= iterations; pos++) {


        Serial.print("ERROR: ");
        Serial.println(servo.getError());

        servoPos = 10 + 160 * QuadraticEaseIn(pos/iterations);

        Serial.print("POS: ");
        Serial.println(servoPos);

        servo.write(servoPos);

        delay(2000);
    }




    /*for (pos = iterations; pos >= 0; pos--) {

        Serial.println(servo.getError());

        servoPos = 10 + 160 * QuadraticEaseOut(pos/iterations);

        servo.write(servoPos);

        delay(2000);

    }*/


}

