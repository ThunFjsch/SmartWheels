#ifndef MotorModule_H
#define  MotorModule_H
#include <Arduino.h>
#include <time.h>
	void initMotorModule(int _leftMotorSide, int _rightMotorSide, int _enablePWMLeft, int _enablePWMRight, bool debug);
	void stopMotors();
	
	/* ========================= Speed/Direction functions ================================= */
	void setAllMotorSpeed(int newSpeed);
	void setLeftMotorSpeed(int newSpeed);
	void setRightMotorSpeed(int newSpeed);
	void setMotorDirection(bool direction);
	
	/* ========================= Steering functions ================================= */
	void steerLeftSimple(int leftMotorForce);
	void steerRightSimple(int rightMotorForce);
	void complexSteering(int rightMotorForce, int leftMotorForce);
	
	/* ========================= Testing functions ================================= */
	void motorLinearIncreaseTest();
	void motorHighDrasticSpeedChange();
	void forwardBackwardsDrivingTest();
	void simpleSteeringTest();
	void complexSteeringTest();
#endif
