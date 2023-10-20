#ifndef SonarModule_H
#define SonarModule_H
#include <Arduino.h>

void initSonarModule(int _trigPin, int _echoPinBack, int _echoPinCenter, int _echoPinLeft, int _echoPinRight);
void updatedSonarDistance();
float GetAllFrontDistance();
float GetBackDistance();
bool isSomethingFront(int distance);
void TestingDistanceAndAccuracy();
void sonarDebug();

#endif
