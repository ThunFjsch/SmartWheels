#include <time.h>
TESTIN false
int brushMotorEnablePin = 8;   // Is connected to the blue wire
int brushMotorPWMPin = 9;   // Is connected to the green wire
// TODO: create function that returns strength 0-255 with input in %
int brushMotorStrength = 240;    // the higher the number the lower the strength

void setup() {
  // Setup HBridge Pins
  pinMode(brushMotorEnablePin, OUTPUT);
  digitalWrite(brushMotorEnablePin, LOW);
  pinMode(brushMotorPWMPin, OUTPUT);
  analogWrite(brushMotorPWMPin, 255);

  // Debug & testing
  if(testing){
    Serial.begin(9600);
    brushMotorCycleTest(brushMotorEnablePin, brushMotorPWMPin);
    brushMotorHighDrasticSpeedChange(brushMotorEnablePin, brushMotorPWMPin);
  }
}

void loop() {
}

// So that other Modules can set the speed of the vehicle
void setBrushMotorSpeed(){}



// Starts at high motor speeds and degrades the speed over time
void brushMotorCycleTest(int brushMotorEnablePin, int brushMotorPWMPin){
  digitalWrite(enable, HIGH);
  for(int i = 0; i <= 255;){    // remember 255 is the upper Motor limit
    analogWrite(brushMotorPWMPin, i);
    delay(100);
    i++;
  }
  digitalWrite(brushMotorEnablePin, LOW);
}

// has various speeds which get selected every 200ms by a randome number
void brushMotorHighDrasticSpeedChange(int brushMotorEnablePin, int brushMotorPWMPin){
  int randomeNumber;
  int arrayLength = 8;
  int differentSpeeds[arrayLength] = {0, 50, 100, 150, 180, 200, 230, 250};   // various speeds can be added later
  digitalWrite(brushMotorEnablePin, HIGH);
  
  for(int i = 0; i <= 30;){
    randomeNumber = random(0, arrayLength);     // 0 min 8 max
    analogWrite(brushMotorPWMPin, differentSpeeds[randomeNumber]);
    Serial.println(differentSpeeds[randomeNumber]);
    delay(200);
    i++;
  }
}
