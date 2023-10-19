#include "MotorModule.h"
#include "OLEDScreen.h"

// Pin IO Mode definition
#define modeSwitchButton 6

// Pin Motor definition
#define leftMotorPinSide 8    // is connected with Inverter Input A1
#define rightMotorPinSide 9   // is connected with Inverter Input A2
#define enablePWMPinLeft 10   // is connected with blue wire
#define enablePWMPinRight 11  // is connected with white wire
  
bool directionGasReverse = true; // Forward
bool directionTurn = true; // Left
bool debug = true;

void setup() {
  Serial.begin(9600);
  // Here the initialisation of the MotorModule is called
  // the true will execute the Debug code
  initMotorModule(leftMotorPinSide, rightMotorPinSide, enablePWMPinLeft, enablePWMPinRight, debug );
  initIOModule(modeSwitchButton, directionGasReverse, directionTurn, debug );
}


void loop() {
  showTime();
  timeSave();
  drawDisplayBitmaps();
  if(debug){
    testBitmaps();
  }
}