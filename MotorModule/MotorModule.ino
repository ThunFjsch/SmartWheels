#include <time.h>
int leftMotorSide = 8;   // is connected with yellow wire
int rightMotorSide = 9;   // is connected with brown wire
int enablePWMPinLeft = 10;   // is connected with blue wire
int enablePWMPinRight = 11;  // is connected with white wire
// TODO: create function that returns strength 0-255 with input in %
int brushMotorStrength = 240;    // the higher the number the lower the strength

void setup() {
  // Setup HBridge Pins
  pinMode(leftMotorSide, OUTPUT);
  digitalWrite(leftMotorSide, LOW);
  pinMode(rightMotorSide, OUTPUT);
  digitalWrite(rightMotorSide, LOW);
  pinMode(enablePWMPinLeft, OUTPUT);
  pinMode(enablePWMPinRight, OUTPUT);
  Serial.begin(9600);
  Serial.println("test");

  // Debug & testing.
  if(true){
    motorLinearIncreaseTest();
    motorHighDrasticSpeedChange();
    forwardBackwardsDrivingTest();
    simpleSteeringTest();
    complexSteeringTest();
    stopMotors();
  }
  
}

void loop(){}

void stopMotors(){
  setAllMotorSpeed(0);
}

/* ========================= Speed/Direction functions ================================= */

// So that other Modules can set the speed of the vehicle
// Set Speed between 0 - 255
void setAllMotorSpeed(int newSpeed){
  analogWrite(enablePWMPinLeft, newSpeed);
  analogWrite(enablePWMPinRight, newSpeed);
}

void setLeftMotorSpeed(int newSpeed){
  analogWrite(enablePWMPinLeft, newSpeed);
}

void setRightMotorSpeed(int newSpeed){
  analogWrite(enablePWMPinRight, newSpeed);
}

// direction true is forward, false backwards
void setMotorDirection(bool direction){
  // forward direction
  if(direction){
    digitalWrite(leftMotorSide, LOW);
    digitalWrite(rightMotorSide, LOW);
  }
  // backward direction
  else if(!direction){
    digitalWrite(leftMotorSide, HIGH);
    digitalWrite(rightMotorSide, HIGH);
  }
}

/* ========================= Steering functions ================================= */

// Simple steering sets one sides motor force to 0 and sets the other to a value between 0 - 255
void steerLeftSimple(int leftMotorForce){
  setLeftMotorSpeed(leftMotorForce);   // the force the leftside motors should be driven with
  setRightMotorSpeed(0);   // with simplesteering only one sides moves
}

void steerRightSimple(int rightMotorForce){
  setRightMotorSpeed(rightMotorForce);   // the force the leftside motors should be driven with
  setLeftMotorSpeed(0);   // with simplesteering only one sides moves
}

// Complex steering takes the individual speeds for both sides
// because of that more complex steering maneuvers are possible 
void complexSteering(int rightMotorForce, int leftMotorForce){
  analogWrite(enablePWMPinLeft, rightMotorForce);
  analogWrite(enablePWMPinRight, leftMotorForce);
}

/* ========================= Testing functions ================================= */


// Starts at high motor speeds and degrades the speed over time
// While testing I observed that the speed on the linearIncrease that the speed at 80 wasn't the same as in the motorHighDrasticSpeedChange
void motorLinearIncreaseTest(){     
  setMotorDirection(true);  
  linearMotorSpeedIncrease();
  setMotorDirection(false);
  linearMotorSpeedIncrease();
  stopMotors();
}

// has various speeds which get selected every 200ms by a randome number
void motorHighDrasticSpeedChange(){
  int randomeNumber;
  int arrayLength = 8;
  int differentSpeeds[arrayLength] = {0, 50, 100, 150, 180, 200, 230, 250};   // various speeds can be added later
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

void simpleSteeringTest(){
  setMotorDirection(true);
  Serial.println("Right");
  steerRightSimple(100);
  delay(2000);
  Serial.println("Left");
  steerLeftSimple(100);
  delay(2000);

  setMotorDirection(false);
  Serial.println("Right");
  steerRightSimple(100);
  delay(2000);
  Serial.println("Left");
  steerLeftSimple(100);
  delay(2000);

  stopMotors();
}

// This test forms more of demonstration how the it could be used. 
// This example increments linear
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

void linearMotorSpeedIncrease(){
  for(int i = 0; i <= 255;){    // remember 255 is the upper Motor limit
    Serial.println(i);
    setAllMotorSpeed(i);
    delay(100);
    i++;
  }
}