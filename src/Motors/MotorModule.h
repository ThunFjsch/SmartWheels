#ifndef MotorModule_H
#define MotorModule_H
#include "../time/timeInterrupt.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>
#include <stdbool.h>

/* ========================= Setup ================================= */
void initMotorModule(bool test);
/* ========================= Steering functions ================================= */
void indicatorLeft();
void indicatorRight();
void resetIndicator()
/* ========================= Speed functions ================================= */
void stopMotors();
void setAllMotorSpeed(uint8_t newSpeed);
void setLeftMotorSpeed(uint8_t newSpeed);
void setRightMotorSpeed(uint8_t newSpeed);
/* ========================= direction functions ================================= */
void setMotorDirection(bool direction);
void setIndividualDirection(bool leftDirection, bool rightDirection);

/* ========================= Steering functions ================================= */
void steerLeftSimple(uint8_t leftMotorForce);
void steerRightSimple(uint8_t rightMotorForce);
void zeroDegreeLeft(uint8_t motorSpeed);
void zeroDegreeRight(uint8_t motorSpeed);
void complexSteering(uint8_t rightMotorForce, uint8_t leftMotorForce);
	
/* ========================= Testing functions ================================= */
void motorLinearIncreaseTest();
void motorHighDrasticSpeedChange();
void forwardBackwardsDrivingTest();
void simpleSteeringTest();
void complexSteeringTest();
#endif
