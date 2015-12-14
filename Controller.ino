#include <Arduino.h>
#include "Motor.h"
#include "OServo.h"
#include <PID_v1.h>
#include "easing.h"

float servoPos, pos;
float iterations = 2000; // Iterationer pr animation


double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp = 10, Ki = 0, Kd = 0;
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


    Serial.println(servo.getError());

    updateLastTime = millis() / 1000;

    servo.update();

    pid.Compute();

    servo.write(0);

    //Setpoint = targetdegree;
    //Input = readdegree;




    /* Serial.print("Output: ");
     Serial.println(Output);

     Serial.print("TARGET: ");
     Serial.println(targetdegree);

     Serial.print("Actual: ");
     Serial.println(readdegree);
 */

    /*
    for (pos = 0; pos <= iterations; pos++) {

        //TODO: Hvad sker der hvis vi bytter om på easein og easeOut?
        servoPos = 10 + 160 * CubicEaseOut(pos/iterations);

        setTargetDegree(servoPos);
        update();

        delay(100);

    }

    for (pos = iterations; pos >= 0; pos--) {

        servoPos = 10 + 160 * CubicEaseIn(pos/iterations);


        setTargetDegree(servoPos);
        update();

        delay(100);


    }
     */



}

