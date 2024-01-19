#include "sonarModule.h"
#include <avr/io.h>
#include <avr/interrupt.h>

enum Sonars {
Left,
Center,
Right	
};

extern volatile uint16_t distanceInCM;
volatile uint8_t pulseCount = 0;
 
int trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight;
float frontDistances[2];

void initSonar(){
	// TODO fuck: We need to activate and deactivate the hardware interrupt before we send out the pulse. Else we will have multiple echo signals overlapping which will skew the count results.
	
	
	// PCMSK2 enables the hardware interrupt for the PD pins
	PCMSK2 |= (1<<PCINT19); // TODO later add the other sonars(1<<PCINT20), (1<<PCINT21);
	PCICR |= (1<<PCIE2);	// If PCIE2 is not set hardware interrupt is not active
}

ISR(PCINT0_vect){
	pulseCount++;
}

void _trigger(){
	// TODO: Trigger is being called in each function of getDistance. In the getDistance function the hardware interrupt pin is set and unsets the other pins.
}

int _calcDistance(int time){
	// TODO: this function is called in each getDistance functions, it returns the calculated distance.
}

int getLeftDistance();
int getCenterDistance();
int getRightDistance();

/*void initSonarModule(){
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
  //float distanceCalc =  0.034 / 2; //distance in cm
 /* 
  frontDistances[0] = pulseIn(echoPinLeft, HIGH) * distanceCalc;
  frontDistances[1] = pulseIn(echoPinCenter, HIGH) * distanceCalc ; 
  frontDistances[2] = pulseIn(echoPinRight, HIGH) * distanceCalc;
  backDistance = pulseIn(echoPinBack, HIGH) * distanceCalc;
  */
}

//Function returns updated front reading in cm. 
/*float GetAllFrontDistance(){
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
/*}

//Function to initiate test
void sonarDebug(){
   TestingDistanceAndAccuracy();
}
*/