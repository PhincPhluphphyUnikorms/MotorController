#include <Arduino.h>
#include "Motor.h"
#include "PIDLibrary/PID_v1.h"




#define degreerange 170 // The range of degrees that the servo can move
#define potirange 1024 // The range of the readings from the poti

#define potimin 118 // The minimal reading that we can get from the poti
#define maxreading 664 // The maximal reading that we can get from the poti
#define potimax potirange - maxreading // The values that the poti will never enter


#define realpotirange abs(potirange-potimax) - potimin // The range of degrees that the servo can move

#define multiplier ((0.00 + degreerange) / (0.00 + realpotirange)) // The range of degrees that the servo can move


int readdegree;
int targetdegree;
float error;

double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

//Makes motor with correct pins
Motor motor(3, 4, 9);


unsigned long updateLastTime = 0;


int degreeFromPotiReading();
void update();
int convertToDegree(int reading);


void setup() {

    Serial.begin(9600);
    pid.SetMode(AUTOMATIC);
    pid.SetOutputLimits(150, 255);

}


void loop() {
    if (millis() - updateLastTime > 20) {
        updateLastTime = millis();
        update();
    }
}

void update() {

    targetdegree = -90;
    Setpoint = targetdegree;

    readdegree = degreeFromPotiReading();
    error = targetdegree - readdegree;

    Input = readdegree;

    pid.Compute();

    //motor.setSpeed(Output);
    motor.move(error, 2);

    Serial.print("Output: ");
    Serial.println(Output);

    Serial.print("TARGET: ");
    Serial.println(targetdegree);

    Serial.print("Actual: ");
    Serial.println(readdegree);

}


int degreeFromPotiReading() {

    int value = analogRead(0);


    value -= potimin;

    return convertToDegree(value);


}

int convertToDegree(int reading) {

    return (reading * multiplier) - (degreerange / 2);

}

