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

  // Debug & testing
  if(true){
    motorLinearIncreaseTest();
    motorHighDrasticSpeedChange();
    forwardBackwardsDrivingTest();
    stopMotors();
  }
}

void loop() {
//forwardBackwardsDrivingTest();
motorLinearIncreaseTest();
    motorHighDrasticSpeedChange();
    forwardBackwardsDrivingTest();
}

// So that other Modules can set the speed of the vehicle
// Set Speed between 0 - 255
void setAllBrushMotorSpeed(int newSpeed){
  analogWrite(enablePWMPinLeft, newSpeed);
  analogWrite(enablePWMPinRight, newSpeed);
}

void setLeftBrushMotorSpeed(int newSpeed){
  analogWrite(enablePWMPinLeft, newSpeed);
}

void setRightBrushMotorSpeed(int newSpeed){
  analogWrite(enablePWMPinRight, newSpeed);
}

// direction true is forward, false backwards
void setBrushMotorDirection(bool direction){
  if (direction){
    digitalWrite(leftMotorSide, LOW);
    digitalWrite(rightMotorSide, LOW);
    Serial.println("forward");
  }
  else if(!direction){
    digitalWrite(leftMotorSide, HIGH);
    digitalWrite(rightMotorSide, HIGH);
    Serial.println("reverse");
  }
}

void stopMotors(){
  setBrushMotorDirection(0);
}

void steerLeftSimple(){
  digitalWrite(leftMotorSide, HIGH);
  digitalWrite(rightMotorSide, LOW);
}

void steerRightSimple(){
  digitalWrite(leftMotorSide, LOW);
  digitalWrite(rightMotorSide, HIGH);
}

/* ========================= Testing functions ================================= */


// Starts at high motor speeds and degrades the speed over time
// While testing I observed that the speed on the linearIncrease that the speed at 80 wasn't the same as in the motorHighDrasticSpeedChange
void motorLinearIncreaseTest(){     
  setBrushMotorDirection(true);  
  for(int i = 0; i <= 255;){    // remember 255 is the upper Motor limit
    Serial.println(i);
    setAllBrushMotorSpeed(i);
    delay(100);
    i++;
  }

  setBrushMotorDirection(false);
  for(int j = 0; j <= 255;){    // remember 255 is the upper Motor limit
    Serial.println(j);
    setAllBrushMotorSpeed(j);
    delay(100);
    j++;
  }

  stopMotors();
}

// has various speeds which get selected every 200ms by a randome number
void motorHighDrasticSpeedChange(){
  int randomeNumber;
  int arrayLength = 8;
  int differentSpeeds[arrayLength] = {0, 50, 100, 150, 180, 200, 230, 250};   // various speeds can be added later
  setBrushMotorDirection(true);
  
  for(int i = 0; i <= 30;){
    randomeNumber = random(0, arrayLength);     // 0 min 8 max
    setAllBrushMotorSpeed(differentSpeeds[randomeNumber]);
    Serial.println(differentSpeeds[randomeNumber]);
    delay(200);
    i++;
  }

  stopMotors();
}

// Testing reverse and forward driving
void forwardBackwardsDrivingTest(){
  setAllBrushMotorSpeed(150);
  setBrushMotorDirection(true);
  delay(2000);
  setBrushMotorDirection(false);
  delay(2000);

  stopMotors();
}