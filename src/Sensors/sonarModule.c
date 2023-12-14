#include "sonarModule.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint16_t distanceInCM;

int trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight;
float backDistance = 0;
float frontDistances[2];

void initSonarModule(){
	cli();
  // Timer setup as fast PWM
	DDRD |= (1<<DDD6);	// Trigger Pin
	TCCR2A = (1<<COM2A1) | (1<<COM2A0) | (1<<WGM21) | (1<<WGM20);
	TCCR2B |= (1<<CS01);	// prescaler = 8 for timer 2
	OCR2A = 235;	// 10us trigger pulse, 118us off-time (128us repetition rate)
	
	// Input configuration
	DDRD &= ~(1<<DDD7);	// PD7 as input
	
	sei();
}

//Function gets updated readings of distance  
void updatedSonarDistance(){
  // updating sonar hardware
	/*
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
*/
 //calculation to convert the reading from the sonar sensor into centimeter. 
  float distanceCalc =  0.034 / 2; //distance in cm
 /* 
  frontDistances[0] = pulseIn(echoPinLeft, HIGH) * distanceCalc;
  frontDistances[1] = pulseIn(echoPinCenter, HIGH) * distanceCalc ; 
  frontDistances[2] = pulseIn(echoPinRight, HIGH) * distanceCalc;
  backDistance = pulseIn(echoPinBack, HIGH) * distanceCalc;
  */
}

//Function returns updated front reading in cm. 
float GetAllFrontDistance(){
  return frontDistances[2];
}
//Function returns updataed back raeding in cm.
float GetBackDistance(){
  return backDistance;
}

//Function to test accuracy of sonar sensors
void TestingDistanceAndAccuracy(){
	/*
  Serial.println(frontDistances[0]);
  Serial.println(frontDistances[1]);
  Serial.println(frontDistances[2]);
  Serial.println(backDistance);
	*/
}

//Function to initiate test
void sonarDebug(){
   TestingDistanceAndAccuracy();
}
