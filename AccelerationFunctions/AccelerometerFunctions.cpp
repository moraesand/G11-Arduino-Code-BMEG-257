#include "AccelerometerFunctions.h"
#include <Arduino.h>

#include <Wire.h> // include library in the future
#include <math.h> 
#include <Adafruit_Sensor.h> // include library in future
#include <Adafruit_ADXL345_U.h> // include library in future

// 10 set as arbituary number, adjust if neccessary
#define WINDOW_SIZE 10 
// again, 0.2 set as an arbituary minimum threshold, adjust if needed 
#define MAX_THRESHOLD 0.2
// unique ID # for ADXL345 device
#define ADXL345_ID_NUMBER 25711

float calculateMagnitude(sensors_event_t event} { 
	accel.getEvent(&event);
	// gets the x, y, z values from reading
	xCoord = acceleration.event.x;
	yCoord = acceleration.event.y;
	zCoord = acceleration.event.z;
	
	return sqrt(xCoord * xCoord + yCoord * yCoord + zCoord * zCoord);
}

// implement the sliding door algorithm
void slidingDoorAlgorithm (int count, int index, float thresholdReadings[WINDOW_SIZE]) {
	// fills up threshold values into array until count reaches WINDOW_SIZE
	if (count < WINDOW_SIZE) {
		thresholdReadings[count];
		count++;
	} else { 
		// takes in a new threshold value and kicks the oldest reading out
		thresholdReadings[index];
		index = (index + 1) % WINDOW_SIZE;
	}
}

// checks if the min max threshold value is under the max threshold requirement
bool isStable(float min, float max) {
	return abs(max - min) < MAX_THRESHOLD;
}
