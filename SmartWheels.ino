#include "MotorModule.h"
#include "IoModule.h"
#include "SonarModule.h"
#include "timeModule.h"
#include "melody.h"
#include "IRModule.h"
#include "Driving.h"
#include "FollowerDriving.h"
#include "AutonomousDriving.h"
#include "bluetooth.h"

// Pin Indicator definition
#define rightIndicatorPin A1
#define leftIndicatorPin A2

// buzzer definition
#define buzzer 3  // TODO: indicate object behind while in reverse

// Pin IO Mode definition
#define modeSwitchButton A3

// these arent used in the codebase but are the default pins for the OLED library
// These pins are utilised in line 4 in the IoModule.cpp
#define serialDataOLED A4
#define serialClockOLED A5

// Pin Motor definition
#define leftMotorPinSide 7    // is connected with Inverter Input A1
#define rightMotorPinSide 4   // is connected with Inverter Input A2
#define enablePWMPinLeft 6   // is connected with blue wire
#define enablePWMPinRight 5  // is connected with white wire

// Sonar module pins
#define trigPin 7 
#define echoPinCenter 5
#define echoPinLeft 6
#define echoPinRight 4


// IR Module definitions
#define irFront A0
#define irLeft 1
#define irRight 2
  
float BackDistance = 0; //Back distance reading
float FrontDistances[2]; //Front distance raeding from three sensors
  
bool directionForwBack = true; // Forward is true. Backward is false
int directionTurn = 0; // 0 straight 1 left 2 right
int state = 0;
int speed = 0;
bool debug = false;

// timing relevant variables
unsigned long currentMillis = 0;

// button debounce
int buttonDebounceTime = 5;
int elapsedButtonDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  initBluetooth();
  initTimeModule();
  initIOModule();
  initMotorModule(leftMotorPinSide, rightMotorPinSide, enablePWMPinLeft, enablePWMPinRight, rightIndicatorPin, leftIndicatorPin, debug);
  initSonarModule(trigPin, echoPinCenter, echoPinLeft, echoPinRight);
  initIRModule(irFront, irLeft, irRight);
  pinMode(modeSwitchButton, INPUT_PULLUP);
  playStartup(buzzer);
}

void loop() {
  if(false){
    testBitmaps();
    sonarDebug();
    TestingIRDetectionAccuracy();
  }
  
  // Time
  currentMillis = millis();
  updateCarTime(currentMillis);
  saveCarTime();

  // State Change
  updateStateButton();  

  // Draw Display
  drawDisplay(state, speed, directionForwBack, directionTurn, getHours(), getMinutes(), getSeconds());  // TODO: Fix the time Display, currently wrong time like 0:97:00 is being displayed

  // Update Sensors
  updatedSonarDistance();
  updatedIRDetection();

  // car state logic
  switch(state){
    case 0:
      Serial.println("RC Mode");
      bluetooth(speed, directionTurn, directionForwBack);
      // TODO: Update speed, direction and directionForwBack in the ino. So the OLED can display it correctly
      break;
    case 1:
      Serial.println("AT Mode");
      runAutonomous(speed);
      speed = getAutonomSpeed();
      directionTurn = getDrivingDirection();
      break;
    case 2:
      Serial.println("SM Mode");
      runFollower(speed);
      directionTurn = getDrivingDirection();
      speed = getFollowerSpeed();
  }
}

void updateStateButton(){
  if(digitalRead(modeSwitchButton) == LOW) { // Temporary button switching
    if(elapsedButtonDebounceTime >= buttonDebounceTime){
      state++;
      elapsedButtonDebounceTime = 0;
      if(state > 2){
        state = 0;
      }
    }
  }
  elapsedButtonDebounceTime++;
}