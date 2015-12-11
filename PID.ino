#include <Arduino.h>
#include "Motor.h"


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

//Makes motor with correct pins
Motor motor(3, 4, 9);


unsigned long updateLastTime = 0;


int degreeFromPotiReading();
void update();
int convertToDegree(int reading);


//This is PID!!
void setup() {
>>>>>>> PID

    digitalWrite(enablePin, HIGH);
    Serial.begin(9600);

}


void loop() {
    if (millis() - updateLastTime > 20) {
        updateLastTime = millis();
        update();
    }
}

void update() {

    targetdegree = -70;
    readdegree = degreeFromPotiReading();
    error = targetdegree - readdegree;


    // Serial.print("DEGREE: ");
    // Serial.println(readdegree);



    Serial.print("ERROR: ");
    Serial.println(error);


    if(error <= 10 && -10 <= error) {

        motor.stop();

    } else if(error > 0) {

        motor.counterClockwise();

    } else {

        motor.clockwise();


    }

}


int degreeFromPotiReading() {

    int value = analogRead(0);


    //Serial.print("POTIVALUE: ");
    //Serial.println(value);

    value -= potimin;

    return convertToDegree(value);


}

int convertToDegree(int reading) {

    return (reading * multiplier) - (degreerange / 2);

}

