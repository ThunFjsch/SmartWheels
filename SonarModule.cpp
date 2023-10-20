#include "SonarModule.h"
#include <Arduino.h>

int trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight;
float backDistance = 0;
float frontDistances[2];

// This value is important to calculate the clock cycles from the pulse
#define timeout 8

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
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  //calculation to convert the reading from the sonar sensor into centimeter. 
  float distanceCalc =  0.034 / 2; //distance in cm
  
  frontDistances[0] = pulseIn(echoPinLeft, HIGH, timeout) * distanceCalc;
  frontDistances[1] = pulseIn(echoPinCenter, HIGH, timeout) * distanceCalc; 
  frontDistances[2] = pulseIn(echoPinRight, HIGH, timeout) * distanceCalc;
  backDistance = pulseIn(echoPinBack, HIGH, timeout) * distanceCalc;
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
  Serial.println(frontDistances[0]);
  Serial.println(frontDistances[1]);
  Serial.println(frontDistances[2]);
  Serial.println(backDistance);
  delay(50);
}

//Function to initiate test
void sonarDebug(){
   TestingDistanceAndAccuracy();
}
