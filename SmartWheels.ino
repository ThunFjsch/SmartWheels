#include "MotorModule.h"
#include "IoModule.h"
#include "SonarModule.h"
#include "timeModule.h"
#include "melody.h"

// Pin Indicator definition
#define rightIndicatorPin A1
#define leftIndicatorPin A2

// buzzer definition
#define buzzer 3  // TODO play startup sound and indicate object behin while in reverse

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

//Sonar module pins
#define trigPin 3
#define echoPinBack 8
#define echoPinCenter 9
#define echoPinLeft 10
#define echoPinRight 11

// BT pin definition
#define btRxd 12  // currently not used
#define btTxd 13  // currently not used
  
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
int buttonDebounceTime = 400;
int elapsedButtonDebounceTime = 0;

// Communication values for Mockup Bluetooth
bool stringComplete = false;  // TODO: Remove this when Bluetooth Module is implemented
String inputString = "";  // TODO: Remove this when Bluetooth Module is implemented

void setup() {
  //playStartup(buzzer);
  Serial.begin(9600);
  initTimeModule();
  initIOModule();
  initMotorModule(leftMotorPinSide, rightMotorPinSide, enablePWMPinLeft, enablePWMPinRight, rightIndicatorPin, leftIndicatorPin, debug);
  initSonarModule(trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight);
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

  // Sonar needs to be updated each cycle
  updatedSonarDistance();

  // car state logic
  switch(state){
    case 0:
      Serial.println("RC Mode");
      simulateBT();
      break;
    case 1:
      Serial.println("AT Mode");
      if(!isSomethingFront(15)){
        
      }
      break;
    case 2:
      if(isSomethingFront(15)){
        
      }
      Serial.println("SM Mode");
  }
}

void updateStateButton(){
  if(digitalRead(modeSwitchButton) == LOW) { // Temporary button switching
    if(currentMillis - elapsedButtonDebounceTime >= buttonDebounceTime){
      Serial.println(currentMillis - elapsedButtonDebounceTime);
      state++;
      elapsedButtonDebounceTime = currentMillis;
      if(state > 2){
        state = 0;
      }
    }
  }
}

void autonomousMode(){

}

void simulateBT(){  // TODO: Remove this when Bluetooth Module is implemented
  if(stringComplete){
    stringComplete = false;
    // If u is inputted chase from pin 8 to 13 is active
    if(inputString == "a\n"){
      steerLeftSimple(speed);
      directionTurn = 1;
      inputString = "";
    }
    // if d is inputted chase from pin 13 to 8 is active
    else if(inputString == "d\n"){
      steerRightSimple(speed);
      directionTurn = 2;
      inputString = "";
    }
    else if(inputString == "w\n"){
      directionForwBack = true;
      setMotorDirection(true);
    }
    else if(inputString == "s\n"){
      directionForwBack = false;
      setMotorDirection(false);
    }
    else if(inputString == "q\n"){
      speed += 20;
      directionTurn = 0;
      if(speed > 255){
        speed = 255;
      }
      setAllMotorSpeed(speed);
    }
    else if(inputString == "e\n"){
      speed -= 20;
      directionTurn = 0;
      if(speed < 0){
        speed = 0;
      }
      setAllMotorSpeed(speed);
    }
    else if(inputString == " \n"){
      stopMotors();
      speed = 0;
    }
    else {
      // if invalid input resets inputString
      inputString = "";
    }
  }
}

// Bluetooth Mockup
void serialEvent() {  // TODO: Remove this when Bluetooth Module is implemented
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      Serial.println(inputString);
    }
  }
}