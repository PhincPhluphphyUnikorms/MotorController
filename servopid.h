#ifndef __SERVOPID
#define __SERVOPID

#include <Arduino.h>
#include <stdio.h>

//This is master!!!!
#define motor1Pin1 3 // pin 2 on L293D
#define motor1Pin2 4 // pin 7 on L293D

#define degreerange 170 // The range of degrees that the servo can move
#define potirange 1024 // The range of the readings from the poti

#define potimin 118 // The minimal reading that we can get from the poti
#define maxreading 664 // The maximal reading that we can get from the poti
#define potimax potirange - maxreading // The values that the poti will never enter


#define realpotirange abs(potirange-potimax) - potimin // The range of degrees that the servo can move

#define multiplier ((0.00 + degreerange) / (0.00 + realpotirange)) // The range of degrees that the servo can move


class PIDServo {
private:
    float P_GAIN;
    float I_GAIN;
    float D_GAIN;

    float I;
    float D;
    float I_LIM;
    float E0;

    float GAIN;
    float error;


public:
    int readdegree;
    int targetdegree;


    void begin() {
        // Start values
        P_GAIN = 1; // Properpotional gain fejlen som bliver sendt til motoren
        I_GAIN = 0.05; // lack gaing - hvis den ikke kan komme igang
        D_GAIN = 0.5; // leader jerke
        GAIN = 1.5; // multiplication factor
        Serial.begin(9600);


    }

    void update() {

        targetdegree = 50;
        readdegree = degreeFromPotiReading();
        error = targetdegree - readdegree;


       // Serial.print("DEGREE: ");
       // Serial.println(readdegree);



        Serial.print("ERROR: ");
        Serial.println(error);


        if(error <= 10 && -10 <= error) {

            stop();

        } else if(error > 0) {

            counterClockwise();

        } else {

            clockwise();


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

    void setMoving(int f) {
    }


    void clockwise() {

        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);


    }


    void counterClockwise() {

        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);

    }

    void stop() {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);

    }


};


#endif