#include "IRModule.h"
#include <Arduino.h>

//leds for testing IR sensor
bool IRFront, IRLeft, IRRight;
//Reading from IR sensors are saved in these variables
bool ReadingIRF, ReadingIRL, ReadingIRR; // IRF= IR Front, IRL= IR Left, IRR = IR Right

void initIRModule(bool _IRFront, bool _IRLeft, bool _IRRight){
  IRFront = _IRFront;
  IRLeft = _IRLeft;
  IRRight = _IRRight; 

  pinMode(IRFront, OUTPUT);
  pinMode(IRLeft, OUTPUT);
  pinMode(IRRight, OUTPUT);
}

//Gets updated readings from the IR sensors
void updatedIRDetection(){
  ReadingIRF = digitalRead(IRFront);
  ReadingIRL = digitalRead(IRLeft);
  ReadingIRR = digitalRead(IRRight);
}
//Returns reading from the center IR sensor
bool GetFrontIR(){
  return ReadingIRF;
}
//Returns reading from the left IR sensor
bool GetLeftIR(){
  return ReadingIRL;
}
//Returns reading from the right IR sensor
bool GetRightIR(){
  return ReadingIRR;
}
void TestingIRDetectionAccuracy(){
  Serial.println(ReadingIRF);
  Serial.println(ReadingIRL);
  Serial.println(ReadingIRR);
  delay(50);
}
void IRDebug(){
  TestingIRDetectionAccuracy();
}