#include "MotorModule.h"
#include "/time/timeInterrupt.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>
#include <stdbool.h>

/* ========================= Setup ================================= */
#define blinkInterval 400
uint32_t currentIndicater = 0;
uint32_t previousIndicater = 0;

// debug will allow the run of tests
void initMotorModule(bool test) {
	// Control Pins
	DDRB |= 1<<PINB0 | 1<<PINB3 | 1<<PINB1 | 1<<PINB2;	// IN1/2 | IN3/4 | ENA | ENB
	
	// Timer/Counter0
	TCCR1A |= 1<<WGM11 | 1<<WGM10 | 1<<COM1A1 | 1<<COM1B1;
	TCCR1B |= 1<<CS12 | 1<<CS10;
	
	// Indicator LED lights
	DDRC |= (1<<DDC1) | (1<<DDC2);
	
	// Debug & testing
	if(test){
		setAllMotorSpeed(240);
		setMotorDirection(true);
		setMotorDirection(false);
		steerRightSimple(200);
		steerLeftSimple(200);
		zeroDegreeLeft(200);
		zeroDegreeRight(200);
		setAllMotorSpeed(250);
		// Frieda: The time delays are not really working.
		//				Maybe need some replacement with interrupt timer
		//				But the functions can be tested in the debugger with breakpoints.
		//				The functions to call are prepared above
/*		motorLinearIncreaseTest();
		motorHighDrasticSpeedChange();
		forwardBackwardsDrivingTest();
		simpleSteeringTest();
		complexSteeringTest();
		stopMotors();
		*/
	}
}

/* ========================= indicator functions ================================= */

void indicatorLeft(){
	currentIndicater = millis();
	if((currentIndicater - previousIndicater) >= blinkInterval){
		previousIndicater = currentIndicater;
	  PORTC ^= (1<<DDC1);	//PC1
	}
}

void indicatorRight(){
	currentIndicater = millis();
	if((currentIndicater - previousIndicater) >= blinkInterval){
		previousIndicater = currentIndicater;
		PORTC ^= (1<<DDC2); //PC2
	}
}

void resetIndicator(){
	PORTC &= ~(1<<PORTC1);
	PORTC &= ~(1<<PORTC2);
}

/* ========================= Speed/Direction functions ================================= */

void stopMotors(){
	OCR1A = 0;	// PB1
	OCR1B = 0;  // PB2
}

// MotorSpeeds should always be between 0 - 255 | The range of the MotorSpeed
// Sets the speed on both motors at once
void setAllMotorSpeed(uint8_t newSpeed){
	resetIndicator();
	OCR1A = newSpeed;
	OCR1B = newSpeed;
}

// Only changes the speed in the left motor side
// Without influencing the other motor
void setLeftMotorSpeed(uint8_t newSpeed){
	OCR1A = newSpeed;
}

// Only changes the speed in the right motor side
// Without influencing the other motor
void setRightMotorSpeed(uint8_t newSpeed){
	OCR1B = newSpeed;
}

/* ========================= Direction functions ================================= */

// Sets the driving direction of the car
void setMotorDirection(bool direction){
	// forward direction
	// true is forward
	if(direction){
		PORTB &= ~(1<<DDB0);
		PORTB &= ~(1<<DDB3);
	}
	// backward direction
	// false is backwards
	else if(!direction){
		PORTB |= (1<<DDB0);
		PORTB |= (1<<DDB3);
	}
}

void setIndividualDirection(bool leftDirection, bool rightDirection){
	if(leftDirection){
		PORTB &= ~(1<<DDB0);
	} else {
		PORTB &= (1<<DDB0);
	}
	
	if(rightDirection){
		PORTB &= ~(1<<DDB3);
	} else {
		PORTB |= (1<<DDB3);
	}
}

/* ========================= Steering functions ================================= */

// Sets the leftMotorForce to some speed and sets the right motor to 0
void steerLeftSimple(uint8_t leftMotorForce){
	setLeftMotorSpeed(leftMotorForce);
	setRightMotorSpeed(0);
	indicatorLeft();
}

// Sets the rightMotorForce to some speed and sets the right motor to 0
void steerRightSimple(uint8_t rightMotorForce){
	setRightMotorSpeed(rightMotorForce);
	setLeftMotorSpeed(0);
	indicatorRight();
}

void zeroDegreeLeft(uint8_t motorSpeed){
	setIndividualDirection(false, true);
	setAllMotorSpeed(motorSpeed);
	indicatorLeft();
}

void zeroDegreeRight(uint8_t motorSpeed){
	setIndividualDirection(true, false);
	setAllMotorSpeed(motorSpeed);
	indicatorRight();
}

// Complex steering takes the individual speeds for both sides
// because of that more complex steering maneuvers are possible
void complexSteering(uint8_t rightMotorForce, uint8_t leftMotorForce){
	setLeftMotorSpeed(leftMotorForce);
	setRightMotorSpeed(rightMotorForce);
}

/* ========================= Testing functions ================================= */

void motorLinearIncreaseTest(){
	// While driving forward increases the speed linear over time
	setMotorDirection(true);
	for(int i = 0; i <= 255;){
		setAllMotorSpeed(i);
		_delay_ms(100);
		i++;
	}
	
	// Drives backwards while increasing speed
	setMotorDirection(false);
	for(int i = 0; i <= 255;){
		setAllMotorSpeed(i);
		_delay_ms(500);
		i++;
	}
	stopMotors();
}

// Changes every 200ms the selected speed
void motorHighDrasticSpeedChange(){
	int randomeNumber;
	int arrayLength = 8;
	int differentSpeeds[8] = {0, 50, 100, 150, 180, 200, 230, 250};   // various sppeds to randomly choose from
	
	setMotorDirection(true);
	for(int i = 0; i <= 3000;){
		randomeNumber = random(0, arrayLength);     // 0 min 8 max
		setAllMotorSpeed(differentSpeeds[randomeNumber]);
		_delay_ms(1000);
		i++;
	}

	setMotorDirection(false);
	for(int i = 0; i <= 3000;){
		randomeNumber = random(0, arrayLength);     // 0 min 8 max
		setAllMotorSpeed(differentSpeeds[randomeNumber]);
		_delay_ms(1000);
		i++;
	}
	stopMotors();
}

// Testing reverse and forward driving
void forwardBackwardsDrivingTest(){
	setAllMotorSpeed(150);
	setMotorDirection(true);
	_delay_ms(2000);
	setMotorDirection(false);
	_delay_ms(2000);

	stopMotors();
}

//
void simpleSteeringTest(){
	// Right side forwards
	setMotorDirection(true);
	steerRightSimple(100);
	_delay_ms(2000);
	// Backwards
	setMotorDirection(false);
	steerRightSimple(100);
	_delay_ms(2000);
	

	// Left side forwards
	steerLeftSimple(100);
	_delay_ms(2000);
	// Backwards
 _delay_ms(2000);
	steerLeftSimple(100);
	_delay_ms(2000);

	stopMotors();
}

// This test forms more of demonstration how the it could be used.
// This example increases linear
void complexSteeringTest(){
	int leftMotorForce = 40;  // starting with higher speed than rightMotorForce
	for(int rightMotorForce = 0; rightMotorForce <= 255;){
		complexSteering(rightMotorForce, leftMotorForce);
		_delay_ms(100);
		
		if(leftMotorForce == 255){
			leftMotorForce--;
		}
		else{
			leftMotorForce++;
		}
		rightMotorForce++;
	}
	stopMotors();
}
