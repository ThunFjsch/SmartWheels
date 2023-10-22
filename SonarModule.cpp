#include "SonarModule.h"
#include <Arduino.h>

enum Sensor {
  center = 0,
  left = 1,
  right = 2
};

int trig, echoBack, echoCenter, echoLeft, echoRight;
float backDistance;
float frontDistances[2];
float distance;

// This value is important to calculate the clock cycles from the pulse
#define timeout 2

void initSonarModule(int _trigPin, int _echoPinBack, int _echoPinCenter, int _echoPinLeft, int _echoPinRight){  
  // Sets the given PinLayout to global variables
  trig = _trigPin;
  echoBack = _echoPinBack;
  echoCenter = _echoPinCenter; 
  echoLeft = _echoPinLeft;
  echoRight = _echoPinRight;

 //Setup Sonar Pins
  pinMode(trig, OUTPUT);
  pinMode(echoBack, INPUT);  
  pinMode(echoCenter, INPUT);
  pinMode(echoLeft, INPUT);  
  pinMode(echoRight, INPUT);
}

//calculation to convert the reading from the sonar sensor into centimeter. 
float calcDistance(unsigned long pulse, int echoPin){
  return (pulseIn(echoPin, HIGH) * 0.034)/2;
}

void triggerPulse(){
  // updating sonar hardware
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trig on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}

//Function gets updated readings of distance  
void updatedSonarDistance(){
  triggerPulse();
  frontDistances[center] = calcDistance(pulseIn(echoCenter, HIGH, NULL), echoCenter);
  triggerPulse();
  frontDistances[left] = calcDistance(pulseIn(echoLeft, HIGH, NULL), echoLeft);
  triggerPulse();
  frontDistances[right] = calcDistance(pulseIn(echoRight, HIGH, NULL), echoRight);
  triggerPulse();
  backDistance = calcDistance(pulseIn(echoBack, HIGH, NULL), echoBack);
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
  Serial.print("Center: ");
  Serial.println(frontDistances[center]);
  Serial.print("left: ");
  Serial.println(frontDistances[left]);
  Serial.print("right: ");
  Serial.println(frontDistances[right]);
  Serial.print("back: ");
  Serial.println(backDistance);
}

//Function to initiate test
void sonarDebug(){
   TestingDistanceAndAccuracy();
}
