#include "SonarModule.h"

float BackDistance = 0;
float FrontDistances[2];

#define trigPin 0
#define echoPinBack 1
#define echoPinCenter 3
#define echoPinLeft 5
#define echoPinRight 7
bool bibupDebug = true;
void setup() {
  Serial.begin(9600);
  initSonarModule(trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight);
}

void loop() {
  if(bibupDebug){
    sonarDebug();
  }
}




