#include "MotorModule.h"
#include "IoModule.h"
#include "SonarModule.h"
#include "timeModule.h"

// Pin IO Mode definition
#define modeSwitchButton A3
// these arent used in the codebase but are the default pins for the OLED library
// These pins are utilised in line 4 in the IoModule.cpp
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
  
bool directionForwBack = true; // Forward is true. Backward is false
int directionTurn = 0; // Left is true. False is right
int state = 0;
int speed = 0;
bool debug = false;

// timing relevant variables
unsigned long currentMillis = 0;

// foo
int buttonDebounceTime = 400;
int elapsedButtonDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  initTimeModule();
  initIOModule();
  //initMotorModule(leftMotorPinSide, rightMotorPinSide, enablePWMPinLeft, enablePWMPinRight, debug );
  //initSonarModule(trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight);
  pinMode(modeSwitchButton, INPUT_PULLUP);
}

void loop() {
  if(debug){
    testBitmaps();
    //sonarDebug();
  }

  // Time
  currentMillis = millis();
  updateCarTime(currentMillis);
  saveCarTime();

  // State Change
  updateStateButton();  

  // Draw Display
  drawDisplay(state, speed, directionForwBack, directionTurn, getCarTime());  // TODO: Fix the time Display, currently wrong time like 0:97:00 is being displayed
}

void updateStateButton(){
  if(digitalRead(modeSwitchButton) == LOW) { // Temporary button switching
    if(currentMillis - elapsedButtonDebounceTime >= buttonDebounceTime){
      state++;
      elapsedButtonDebounceTime = currentMillis;
      if(state > 2){
        state = 0;
      }
    }
  }
}