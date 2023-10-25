#ifndef SonarModule_H
#define SonarModule_H
#include <Arduino.h>

void initSonarModule(int _trigPin, int _echoPinCenter, int _echoPinLeft, int _echoPinRight);
void updatedSonarDistance();
float getCenterDistance();
float getLeftDistance();
float getRightDistance();
bool isSomethingFront(int distance);
bool isSomethingInRange(int min, int max);
void TestingDistanceAndAccuracy();
void sonarDebug();

#endif
