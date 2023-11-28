#include "MotorModule.h"
#include "OLEDScreen.h"
#include "SonarModule.h"

// Pin IO Mode definition




  
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