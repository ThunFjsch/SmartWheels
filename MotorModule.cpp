#include <time.h>
#include <Arduino.h>
#include "MotorModule.h"

int leftMotorSide;   // is connected to 1A on the Inverter
int rightMotorSide;   // is connected to 2A on the Inverter
int enablePWMLeft;   // is connected with blue wire
int enablePWMRight;  // is connected with white wire

// the first 4 variable are the Pins for the MotorModule
// debug will allow the run of tests
void initMotorModule(int _leftMotorSide, int _rightMotorSide, int _enablePWMLeft, int _enablePWMRight, bool debug) {
  // Sets the given PinLayout to global variables
  leftMotorSide = _leftMotorSide;
  rightMotorSide = _rightMotorSide;
  enablePWMLeft = _enablePWMLeft;
  enablePWMRight = _enablePWMRight;
   
  // Setup HBridge Pins
  pinMode(leftMotorSide, OUTPUT);
  digitalWrite(leftMotorSide, LOW);
  pinMode(rightMotorSide, OUTPUT);
  digitalWrite(rightMotorSide, LOW);
  pinMode(enablePWMLeft, OUTPUT);
  pinMode(enablePWMRight, OUTPUT);

  // Debug & testing
  if(debug){
    Serial.println("test");
    motorLinearIncreaseTest();
    motorHighDrasticSpeedChange();
    forwardBackwardsDrivingTest();
    simpleSteeringTest();
    complexSteeringTest();
    stopMotors();
  }
}

/* ========================= Speed/Direction functions ================================= */

void stopMotors(){
  setAllMotorSpeed(0);
}

// MotorSpeeds should always be between 0 - 255 | The range of the MotorSpeed
// Sets the speed on both motors at once
void setAllMotorSpeed(int newSpeed){
  analogWrite(enablePWMLeft, newSpeed);
  analogWrite(enablePWMRight, newSpeed);
}

// Only changes the speed in the left motor side
// Without influencing the other motor
void setLeftMotorSpeed(int newSpeed){
  analogWrite(enablePWMLeft, newSpeed);
}

// Only changes the speed in the right motor side
// Without influencing the other motor
void setRightMotorSpeed(int newSpeed){
  analogWrite(enablePWMRight, newSpeed);
}

// Sets the driving direction of the car
void setMotorDirection(bool direction){
  // forward direction
  // true is forward
  if(direction){
    digitalWrite(leftMotorSide, LOW);
    digitalWrite(rightMotorSide, LOW);
  }
  // backward direction
  // false is backwards
  else if(!direction){
    digitalWrite(leftMotorSide, HIGH);
    digitalWrite(rightMotorSide, HIGH);
  }
}

/* ========================= Steering functions ================================= */

// Sets the leftMotorForce to some speed and sets the right motor to 0
void steerLeftSimple(int leftMotorForce){
  setLeftMotorSpeed(leftMotorForce);
  setRightMotorSpeed(0);
}

// Sets the rightMotorForce to some speed and sets the right motor to 0
void steerRightSimple(int rightMotorForce){
  setRightMotorSpeed(rightMotorForce);
  setLeftMotorSpeed(0);
}

// Complex steering takes the individual speeds for both sides
// because of that more complex steering maneuvers are possible 
void complexSteering(int rightMotorForce, int leftMotorForce){
  analogWrite(enablePWMLeft, rightMotorForce);
  analogWrite(enablePWMRight, leftMotorForce);
}

/* ========================= Testing functions ================================= */

void motorLinearIncreaseTest(){
  // While driving forward increases the speed linear over time
  setMotorDirection(true);  
  for(int i = 0; i <= 255;){
    Serial.println(i);
    setAllMotorSpeed(i);
    delay(100);
    i++;
  }
  
  // Drives backwards while increasing speed
  setMotorDirection(false);
  for(int i = 0; i <= 255;){
    Serial.println(i);
    setAllMotorSpeed(i);
    delay(100);
    i++;
  }
  stopMotors();
}

// Changes every 200ms the selected speed
void motorHighDrasticSpeedChange(){
  int randomeNumber;
  int arrayLength = 8;
  int differentSpeeds[arrayLength] = {0, 50, 100, 150, 180, 200, 230, 250};   // various sppeds to randomly choose from
  
  setMotorDirection(true);
  for(int i = 0; i <= 30;){
    randomeNumber = random(0, arrayLength);     // 0 min 8 max
    setAllMotorSpeed(differentSpeeds[randomeNumber]);
    Serial.println(differentSpeeds[randomeNumber]);
    delay(200);
    i++;
  }

  setMotorDirection(false);
  for(int i = 0; i <= 30;){
    randomeNumber = random(0, arrayLength);     // 0 min 8 max
    setAllMotorSpeed(differentSpeeds[randomeNumber]);
    Serial.println(differentSpeeds[randomeNumber]);
    delay(200);
    i++;
  }
  stopMotors();
}

// Testing reverse and forward driving
void forwardBackwardsDrivingTest(){
  setAllMotorSpeed(150);
  setMotorDirection(true);
  delay(2000);
  setMotorDirection(false);
  delay(2000);

  stopMotors();
}

// 
void simpleSteeringTest(){
  // Right side forwards
  setMotorDirection(true);
  Serial.println("Right");
  steerRightSimple(100);
  delay(2000);
  // Backwards
  setMotorDirection(false);
  Serial.println("Right");
  steerRightSimple(100);
  delay(2000);

  // Left side forwards
  Serial.println("Left");
  steerLeftSimple(100);
  delay(2000);
  // Backwards
  Serial.println("Left");
  steerLeftSimple(100);
  delay(2000);

  stopMotors();
}

// This test forms more of demonstration how the it could be used. 
// This example increases linear
void complexSteeringTest(){
  int leftMotorForce = 40;  // starting with higher speed than rightMotorForce
  for(int rightMotorForce = 0; rightMotorForce <= 255;){    
    Serial.print("rightMotorForce: ");
    Serial.println(rightMotorForce);
    Serial.print("leftMotorForce: ");
    Serial.println(leftMotorForce);

    complexSteering(rightMotorForce, leftMotorForce);
    delay(100);
    
    if(leftMotorForce == 255){
      leftMotorForce--;
    } 
    else{
      leftMotorForce++;
    }
    rightMotorForce++;
  }

  stopMotors();
}
