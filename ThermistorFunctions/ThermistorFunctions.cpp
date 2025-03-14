#include "ThermistorFunctions.h"
#include <Arduino.h>

#include <math.h> 

// thermistor pin location
#define THERMISTOR_PIN A0  // analog pin connected to the thermistor (change if needed)

// Steinhart-Hart coefficients (from thermistor datasheet) (change if needed)
#define C1 1.009249522e-03
#define C2 2.378405444e-04
#define C3 2.019202697e-07

// thermistor resistance at 25C (change if needed)
#define SERIES_RESISTOR 10000.0 // 10kΩ fixed resistor

float measureTemperature() {
    float Vo = analogRead(THERMISTOR_PIN);
    float R2 = SERIES_RESISTOR * (1023.0 / Vo - 1.0);

    float tempK = steinhartK(R2, C1, C2, C3);

    // Convert Kelvin to Celsius
    float temperatureC = temperatureK - 273.15;
}

/*
    Use Steinhart-Hart Equation to convert resistance to temperature in Kelvin
    C1, C2, C3 refer to the Steinhart-Hart coefficients (given from thermistor datasheet)
*/ 
float steinhartK(float R2, float C1, float C2, float C3) {
    return 1.0 / (C1 + C2 * log(R2) + C3 * log(R2) * log(R2) * log(R2));
}

bool isOptimalRange(float temp) {
    return temp > 20.0 && temp < 22.0;
}