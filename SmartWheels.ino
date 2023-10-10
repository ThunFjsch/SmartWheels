#include "SonarModule.h"

float BackDistance = 0;
float FrontDistances[2];

#define trigPinBack 0
#define echoPinBack 1
#define trigPinCenter 2
#define echoPinCenter 3
#define trigPinLeft 4
#define echoPinLeft 5
#define trigPinRight 6
#define echoPinRight 7
bool bibupDebug = true;
void setup() {
  Serial.begin(9600);
  initSonarModule(trigPinBack, echoPinBack, trigPinCenter, echoPinCenter, trigPinLeft, echoPinLeft, trigPinRight, echoPinRight);
}

void loop() {
  if(bibupDebug){
    sonarDebug();
  }
}




