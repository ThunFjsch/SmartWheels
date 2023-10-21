#include "SonarModule.h"
#include <Arduino.h>

int trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight;
float backDistance = 0;
float frontDistances[2];
float distance;

// This value is important to calculate the clock cycles from the pulse
#define timeout 2

void initSonarModule(int _trigPin, int _echoPinBack, int _echoPinCenter, int _echoPinLeft, int _echoPinRight){
  
  // Sets the given PinLayout to global variables
  trigPin = _trigPin;
  echoPinBack = _echoPinBack;
  echoPinCenter = _echoPinCenter; 
  echoPinLeft = _echoPinLeft; 
  echoPinRight = _echoPinRight;

 //Setup Sonar Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinBack, INPUT);  
  pinMode(echoPinCenter, INPUT);
  pinMode(echoPinLeft, INPUT);  
  pinMode(echoPinRight, INPUT);
}

//Function gets updated readings of distance  
void updatedSonarDistance(){
  // updating sonar hardware
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
    //calculation to convert the reading from the sonar sensor into centimeter. 
  float distanceCalc =  0.034 / 2; //distance in cm
  distance = pulseIn(9, HIGH) * distanceCalc;
}

//Function returns updated front reading in cm. 
float getAllFrontDistance(){
  return frontDistances[2];
}
//Function returns updataed back raeding in cm.
float getBackDistance(){
  return backDistance;
}

bool isSomethingFront(int distance){
  for(int i = 0; i < 3;){
    if(frontDistances[i] < distance){
      return true;
    }
  }
  return false;
}

//Function to test accuracy of sonar sensors
void TestingDistanceAndAccuracy(){
  Serial.println(distance);
}

//Function to initiate test
void sonarDebug(){
   TestingDistanceAndAccuracy();
}
