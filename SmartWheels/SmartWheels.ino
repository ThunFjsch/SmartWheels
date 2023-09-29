#include <time.h>
#include "MotorModule.h"

#define leftMotorPinSide 8    // is connected with Inverter Input A1
#define rightMotorPinSide 9   // is connected with Inverter Input A2
#define enablePWMPinLeft 10   // is connected with blue wire
#define enablePWMPinRight 11  // is connected with white wire

void setup() {
  // put your setup code here, to run once:
  initMotorModule(rightMotorPinSide, rightMotorPinSide, enablePWMPinLeft, enablePWMPinRight, false);

    motorLinearIncreaseTest();
    motorHighDrasticSpeedChange();
    forwardBackwardsDrivingTest();
    simpleSteeringTest();
    complexSteeringTest();
    stopMotors();
}

void loop() {
  // put your main code here, to run repeatedly:

}
