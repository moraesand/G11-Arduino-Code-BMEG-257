#include "LCDFunctions.h"
#include <Arduino.h>
#include <string.h>
#include <LiquidCrystal_I2C.h>

void message(string message, LiquidCrystal_I2C &lcd, int duration) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(message);
    delay(duration);
    lcd.clear();
}