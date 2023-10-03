#include "MotorModule.h"

const int leftMotorPinSide = 8;    // is connected with Inverter Input A1
const int rightMotorPinSide = 9;   // is connected with Inverter Input A2
const int  enablePWMPinLeft = 10;   // is connected with blue wire
const int enablePWMPinRight = 11;  // is connected with white wire

void setup() {
  // Here the initialisation of the MotorModule is called
  // the true will execute the Debug code
  initMotorModule(leftMotorPinSide, rightMotorPinSide, enablePWMPinLeft, enablePWMPinRight, true);
}

void loop() {}