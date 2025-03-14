#ifndef THERMISTOR_FUNCTIONS_H
#define THERMISTOR_FUNCTIONS_H

void measureTemperature();

// C1, C2, C3 refer to the Steinhart-Hart coefficients (given from thermistor datasheet)
float steinhartK(float R2, float C1, float C2, float C3); 

bool isOptimalRange(float temp);

#endif