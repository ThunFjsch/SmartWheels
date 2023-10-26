#ifndef Driving_H
#define Driving_H
#include <Arduino.h>
#include "SonarModule.h"
#include "IRModule.h"
#include "MotorModule.h"

void turnLeft(int leftMotorSpeed);
void turnRight(int rightMotorSpeed);
void forwardDrive(int speed);
void correctRangeChange(int speed);
void collisionAvoidanceSpeedControl(int speed);
int getDrivingDirection();
int getDrivingSpeed();
void lineSteeringBehaviour(int speed);
void isOnLine();

#endif