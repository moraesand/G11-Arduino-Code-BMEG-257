#ifndef ACCELEROMETER_FUNCTIONS_H
#define ACCELEROMETER_FUNCTIONS_H

float calculateMagnitude(sensors_event_t event);
void slidingDoorAlgorithm();
bool isStable(float min, float max);

#endif