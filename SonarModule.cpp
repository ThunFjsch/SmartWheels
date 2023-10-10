#include "SonarModule.h"
#include <Arduino.h>

int trigPinBack, echoPinBack, trigPinCenter, echoPinCenter, trigPinLeft, echoPinLeft, trigPinRight, echoPinRight;
float backDistance = 0;
float frontDistances[2];

void initSonarModule(int _trigPinBack, int _echoPinBack, int _trigPinCenter, int _echoPinCenter, int _trigPinLeft, int _echoPinLeft, int _trigPinRight, int _echoPinRight){
 
  trigPinBack = _trigPinBack;
  echoPinBack = _echoPinBack;
  trigPinCenter = _trigPinCenter;
  echoPinCenter = _echoPinCenter; 
  trigPinLeft = _trigPinLeft;
  echoPinLeft = _echoPinLeft; 
  trigPinRight = _trigPinRight;
  echoPinRight = _echoPinRight;

  pinMode(trigPinBack, OUTPUT);
  pinMode(echoPinBack, INPUT);  
  pinMode(trigPinCenter, OUTPUT);
  pinMode(echoPinCenter, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);  
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
}

void updatedSonarDistance(){
  // updating sonar hardware
  digitalWrite(trigPinCenter, HIGH);
  digitalWrite(trigPinLeft, HIGH);
  digitalWrite(trigPinRight, HIGH);
  digitalWrite(trigPinBack, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPinCenter, LOW);
  digitalWrite(trigPinLeft, LOW);
  digitalWrite(trigPinRight, LOW);
  digitalWrite(trigPinBack, LOW);

  float distanceCalc =  0.034 / 2; //distance in cm
  
  frontDistances[0] = pulseIn(echoPinLeft, HIGH) * distanceCalc;
  frontDistances[1] = pulseIn(echoPinCenter, HIGH) * distanceCalc ; 
  frontDistances[2] = pulseIn(echoPinRight, HIGH) * distanceCalc;
  backDistance = pulseIn(echoPinBack, HIGH) * distanceCalc;
  
}

float GetAllFrontDistance(){
  return frontDistances[2];
}

float GetBackDistance(){
  return backDistance;
}
void TestingDistanceAndAccuracy(){
  Serial.println(frontDistances[0]);
  Serial.println(frontDistances[1]);
  Serial.println(frontDistances[2]);
  Serial.println(backDistance);
}
void sonarDebug(){
   TestingDistanceAndAccuracy();
}