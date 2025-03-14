/* 
	Code for Acceleromter
	Terms:
		Threshold: refers to the max reading of the acceleration 
		(in x, y, z coordinates) minus the min (max - min)
		
	Made by Samuel An for BMEG 257 Group 11
*/

// libraries for ADXL345
#include <Wire.h> // include library in the future
#include <math.h> 
#include <Adafruit_Sensor.h> // include library in future
#include <Adafruit_ADXL345_U.h> // include library in future

// library for servo motor
#include <Servo.h>

// libraries for LCD screen
#include <string.h>
#include <LiquidCrystal_I2C.h>

// include helper functions
#include "ThermistorFunctions.h"
#include "AccelerometerFunctions.h"
#include "LCDFunctions.h"
#include "ServoFunctions.h"

// 10 set as arbituary number, adjust if neccessary
#define WINDOW_SIZE 10 
// again, 0.2 set as an arbituary minimum threshold, adjust if needed 
#define MAX_THRESHOLD 0.2
// unique ID # for ADXL345 device
#define ADXL345_ID_NUMBER 25711
// max allocated time to find if both conditions to be satisfied (temperature & stability)
#define GRACE_PERIOD 1000

#define SERVO_PIN 10 // arbituary, to be set up later
#define BUTTON_PIN 5 // arbituary, to be set up later

// initialize ADXL345 device to codebase
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(ADXL345_ID_NUMBER); // 25711 is a unique id
float magReadings[WINDOW_SIZE]; // for use to find min, max threshold values 
int count = 0; // # of filled slots in array
int index = 0; // index to replace old values (for sliding door)
bool isStable = false;
bool isOptimalTemp = false;

// initialize servo
Servo injectionDevice;

// initialize LCD screen
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 is the most common i2c address, also try 0x3F

// boolean for if both conditions (temperature & stability) are met
bool condtionsMet = false;

void setup() {
	// init serial monitor (for future debugging)
	Serial.begin(9600);

	// init LCD screen
	lcd.init();
	lcd.backlight();

	// init accelerometer
	// checker for if the accelerometer is broken
	if(!accel.begin()) {
		displayLCD("Error in ADXL345 Accelerometer #25711!", lcd, 2000);
    	while(1);
	}

	// init servo motor
	injectionDevice.attach(SERVO_PIN);

	// init button
	pinMode(BUTTON_PIN, INPUT_PULLUP);

	// msg to signal that device powered on once everything is initalized
	displayLCD("Device is ready for use!", lcd, 1000); 
}

void loop() {
	while (!optimalTemp) {
		// 1. test for optimal temperature
		float tempC = measureTemperature();
		bool isOptimalTemp = isOptimal(tempC);
		if (isOptimalTemp) { lastCheck = millis(); } // start timer if medication reaches optimal temperature
	}

	// 2. test for stability
	// initilize accelerometer
	while (!isStable) {
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
		
		isStable = isStable(minMag, maxMag);
	}

	// checks if the temp is optimal & the device is stable within the grace period of GRACE_PERIOD ms (3000 for now)
	if (isOptimalTemp && isStable && (millis() - lastCheck >= GRACE_PERIOD)) { 
		beepReady();
		displayLCD("Ready for injection!", lcd, 1000); // set up JSON in the future to store messages 
		conditionsMet = true;
	} else { 
		condtionsMet = false; // reset conditionsMet if conditions not met
		if (!(millis() - lastCheck >= GRACE_PERIOD)) { // reset both variables if grace period passed to start the clock again
			isOptimalTemp = false;
			isStable = false;
		}
	} 

	delay(50);

	// inject medicine once the both conditions are met AND button is pressed
	if (condtionsMet && digitalRead(BUTTON_PIN) == HIGH) { // set up debounce for button later
		displayLCD("Injecting...", lcd, 100000);
		moveServo(injectionDevice, 1000); // how long it should move is TBD later in testing (currently 1000ms)
		delay(10000); // wait for a long time before retracting into initial state
		retractServo(injectionDevice, 1000);
		delay(1000);

		lcd.clear();
		displayLCD("Injection is Complete!", lcd, 1000);
	}
}

// BuzzerFunctions, only one so it is in main
void beepReady() { tone(buzzer, 1000, 500); } // beep at 1000 Hz for 500 ms
