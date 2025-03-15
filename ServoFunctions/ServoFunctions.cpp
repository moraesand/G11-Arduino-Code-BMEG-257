#include "ServoFunctions.h"
#include <Arduino.h>

#include <math.h> 
#include <Servo.h>

#define SERVO_PIN 11 // arbituary, to be set up later
#define FULL_BACKWARD_SPEED 0 
#define FULL_FOWARD_SPEED 180
#define STOP 90

void moveServo(Servo servo, int duration) {
    servo.write(FULL_FOWARD_SPEED);
    delay(duration); // move foward fast for 1s, change if necessary
    servo.write(STOP);
}

void retractServo(Servo servo, int duration) {
    servo.write(FULL_BACKWARD_SPEED);
    delay(duration);
    servo.write(STOP);
}


