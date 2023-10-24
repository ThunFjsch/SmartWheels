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
  Serial.println(pulse / 58.2);
  return pulse / 58.2;
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

// TODO: Change the code according to Towfiqs fix
//Function gets updated readings of distance  
void updatedSonarDistance(){
  Serial.println("echo 1");
  triggerPulse();
  frontDistances[center] = calcDistance(pulseIn(echoCenter, HIGH), echoCenter);
  Serial.println("echo 2");
  triggerPulse();
  frontDistances[left] = calcDistance(pulseIn(echoLeft, HIGH), echoLeft);
  triggerPulse();
  Serial.println("echo 3");
  frontDistances[right] = calcDistance(pulseIn(echoRight, HIGH), echoRight);
  triggerPulse();
  Serial.println("echo 4");
  backDistance = calcDistance(pulseIn(echoBack, HIGH), echoBack);
}

//Function returns updated front reading in cm. 
float getAllFrontDistance(){
  return frontDistances[2];
}
//Function returns updataed back raeding in cm.
float getBackDistance(){
  return backDistance;
}

// TODO: It is possible that we need to constrain the distance. Because misreadings etc.
bool isSomethingFront(int distance){
  for(int i = 0; i < 3;){
    if(frontDistances[i] < distance){
      return true;
    }
    i++;
  }
  return false;
}

bool isSomethingInRange(int min, int max){
  for(int i = 0; i < 3;){
    if(frontDistances[i] > min && frontDistances[i] < max){
      return true;
    }
    i++;
  }
  return false;
}

// is being used in the context of range based detirmination
bool toFarOrTooClose(){
  for(int i = 0; i < 3;){
    if(frontDistances[i] < min){
      return true;  // true for under minimum range
    }
    if( frontDistances[i] > max){
      return false; // false for over maximum range
    }
    i++;
  }
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