#ifndef SonarModule_H
#define SonarModule_H
#include <Arduino.h>

void initSonarModule(int _trigPinBack, int _echoPinBack, int _trigPinCenter, int _echoPinCenter, int _trigPinLeft, int _echoPinLeft, int _trigPinRight, int _echoPinRight);
void updatedSonarDistance();
float GetAllFrontDistance();
float GetBackDistance();
void TestingDistanceAndAccuracy();
void sonarDebug();

#endif
