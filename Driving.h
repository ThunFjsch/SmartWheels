#ifndef Driving_H
#define Driving_H
#include <Arduino.h>
#include "SonarModule.h"
#include "IRModule.h"
#include "MotorModule.h"

void initDriving();
void turnLeft(int leftMotorSpeed);
void turnRight(int rightMotorSpeed);
void isOnLine();
void lineSteeringBehaviour();
void correctRangeChange();
void forwardDrive(int speed);
void reverseDrive(int speed);
int getDrivingDirection();
int getManualDirection();
#endif