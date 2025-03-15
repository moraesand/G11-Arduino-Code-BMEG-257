#include "LEDFunctions.h"
#include <Arduino.h>

// flash only once
void lightLED(int pinNumber, int duration) {
    digitalWrite(pinNumber, HIGH);
    delay(duration);
    digitalWrite(pinNumber, LOW);
    delay(duration);
}

// flash multiple times
void flashLED(int pinNumber, int duration, int numOfFlashes) {
    for (int i = 0; i < numOfFlashes, i++) {
        lightLED(pinNumber, duration);
    }
}