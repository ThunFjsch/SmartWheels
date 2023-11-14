#include "MotorModule.h"
#include "OLEDScreen.h"
#include "SonarModule.h"

// Pin IO Mode definition
#define modeSwitchButton 6
// these arent used in the codebase but are the default pins for the OLED library
// These pins are utilised in line 4 in the OLEDScreen.cpp
#define serialDataOLED A4
#define serialClockOLED A5

// Pin Motor definition
#define leftMotorPinSide 8    // is connected with Inverter Input A1
#define rightMotorPinSide 9   // is connected with Inverter Input A2
#define enablePWMPinLeft 10   // is connected with blue wire
#define enablePWMPinRight 11  // is connected with white wire

//Sonar module pins
#define trigPin 0
#define echoPinBack 1
#define echoPinCenter 3
#define echoPinLeft 5
#define echoPinRight 7
  
float BackDistance = 0; //Back distance reading
float FrontDistances[2]; //Front distance raeding from three sensors
  
bool directionGasReverse = true; // Forward is true. Backward is false
bool directionTurn = true; // Left is true. False is right
bool debug = true;

void setup() {
  Serial.begin(9600);
  // Here the initialisation of the MotorModule is called
  // the true will execute the Debug code
  initMotorModule(leftMotorPinSide, rightMotorPinSide, enablePWMPinLeft, enablePWMPinRight, debug );
  initIOModule(modeSwitchButton, directionGasReverse, directionTurn, debug );
  initSonarModule(trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight);
}

void loop() {
  showTime();
  timeSave();
  drawDisplayBitmaps();
  if(debug){
    testBitmaps();
    sonarDebug();
    
  }
}