# G11-Arduino-Code-BMEG-257
This codebase is intended for Group 11's newest medical adherence product for BMEG 257. 

# AccelerometerFunctions
float calculateMagnitude(sensors_event_t event) - calculates magnitude of an acceleration vector<br>
void slidingDoorAlgorithm() - internal use; used to filter out old acceleration readings and put in new ones<br>
bool isStable(float min, float max) - checks if the device is in a stable position<br>

# ThermistorFunctions
void measureTemperature() - reads the temperature at the current moment<br>
float steinhartK(float R2, float C1, float C2, float C3) - internal use; used to calculate temperature using the Steinhart-Hart Equation<br>
bool isOptimalRange(float temp) - checks if the device is in optimal range of use (20-22C)

# ServoFunctions
void moveServo(Servo servo, int duration) - moves servo motor in the forward direction<br>
void retractServo(Servo servo, int duration) - moves servo motor in the backwards direction

# LCDFunctions 
void displayLCD(string message, LiquidCrystal_I2C &lcd, int duration) - displays a string (message) onto the specified LCD screen<br>

# LEDFunctions
void lightLED(int pinNumber, int duration) - lights a specific LED once<br>
void flashLED(int pinNumber, int duration, int numOfFlashes) - lights a specific LED a specified number of times<br> 

# BuzzerFunctions (located in main.ino)
void beepReady() - beeps at 1000 Hz for 500 ms

# Future Updates
For the future, we will be adding:

JSON Support - store all error, success, etc., messages into one JSON that the code can use<br>
Further delay() implmentation - changes to delay() will come in once we start testing the device<br>
Correct pin # and constants - once we start testing, we will be able to come up with the corrent #define constants<br>