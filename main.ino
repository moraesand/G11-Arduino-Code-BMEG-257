/* 
	Code for Acceleromter
	Terms:
		Threshold: refers to the max reading of the acceleration 
		(in x, y, z coordinates) minus the min (max - min)
		
	Made by Samuel An for BMEG 257 Group 11
*/

#include <Wire.h> // include library in the future
#include <math.h> 
#include <Adafruit_Sensor.h> // include library in future
#include <Adafruit_ADXL345_U.h> // include library in future

// include helper functions
#include "ThermistorFunctions.h"
#include "AccelerometerFunctions.h"

// 10 set as arbituary number, adjust if neccessary
#define WINDOW_SIZE 10 
// again, 0.2 set as an arbituary minimum threshold, adjust if needed 
#define MAX_THRESHOLD 0.2
// unique ID # for ADXL345 device
#define ADXL345_ID_NUMBER 25711
// max allocated time to find if both conditions to be satisfied (temperature & stability)
#define GRACE_PERIOD 1000

// initialize ADXL345 device to codebase
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(ADXL345_ID_NUMBER); // 25711 is a unique id
float magReadings[WINDOW_SIZE]; // for use to find min, max threshold values 
int count = 0; // # of filled slots in array
int index = 0; // index to replace old values (for sliding door)
bool isStable;
bool isOptimalTemp;

void setup() {
	lcd.begin(16, 2);
	// checker for if the accelerometer is broken
	if(!accel.begin()) {
		Serial.println("Error in ADXL345 Accelerometer #25711!");
    	while(1);
	}
}

void loop() {
	// 1. test for optimal temperature
	float tempC = measureTemperature();
	bool optimalTemp = isOptimal(tempC);
	if (optimalTemp) { lastCheck = millis(); } // start timer if medication reaches optimal temperature

	// 2. test for stability
	// initilize accelerometer
	sensors_event_t event;
	float magnitudeOne = calculateMagnitude(event); // magnitude of acceleration
	// initiate sliding door algorithm to gather all threshold readings
	slidingDoorAlgorithm(count, index, magReadings);
	
	// add threshold values into array until array is full 
	if (count >= WINDOW_SIZE) { 
		float minMag = magReadings[0];
		float maxMag = magReadings[0];
		
		// find the min/max values of the thresholdReadings array
		for (int i = 1; i < WINDOW_SIZE; i++) {
			if (magReadings[i] < minMag) { minMag = magReadings[i]; }
      		if (magReadings[i] > maxMag) { maxMag = magReadings[i]; }
    	}
	}
	
	// checks if the temp is optimal & the device is stable within the grace period of GRACE_PERIOD ms (3000 for now)
	bool isStable = isStable(minMag, maxMag);
	if (optimalTemp && isStable && (millis() - lastCheck >= GRACE_PERIOD)) { 
		// add something to indicate that it works, maybe green LED flashing and LCD
		// for now, beep
		beepReady();
	}

	delay(100);
}

// adapted from Monitor Temerature
void beepReady() { tone(buzzer, 1000, 500); } // beep at 1000 Hz for 500 ms
