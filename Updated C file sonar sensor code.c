#include "SonarModule.h"

volatile uint8_t trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight;
volatile float backDistance = 0;
volatile float frontDistances[3];

void initSonarModule(uint8_t _trigPin, uint8_t _echoPinBack, uint8_t _echoPinCenter, uint8_t _echoPinLeft, uint8_t _echoPinRight) {
	trigPin = _trigPin;
	echoPinBack = _echoPinBack;
	echoPinCenter = _echoPinCenter;
	echoPinLeft = _echoPinLeft;
	echoPinRight = _echoPinRight;

	// Set trigger pin as output and echo pins as input
	DDRB |= (1 << trigPin);
	DDRB &= ~((1 << echoPinBack) | (1 << echoPinCenter) | (1 << echoPinLeft) | (1 << echoPinRight));

	// Enable pull-up resistors for echo pins
	PORTB |= (1 << echoPinBack) | (1 << echoPinCenter) | (1 << echoPinLeft) | (1 << echoPinRight);
}

void updatedSonarDistance() {
	// Trigger the sonar sensors
	PORTB |= (1 << trigPin);
	_delay_us(10);
	PORTB &= ~(1 << trigPin);

	float distanceCalc = 0.034 / 2;

	// Measure echo time and calculate distances
	frontDistances[0] = pulseIn(echoPinLeft, HIGH) * distanceCalc;
	frontDistances[1] = pulseIn(echoPinCenter, HIGH) * distanceCalc;
	frontDistances[2] = pulseIn(echoPinRight, HIGH) * distanceCalc;
	backDistance = pulseIn(echoPinBack, HIGH) * distanceCalc;
}

float GetAllFrontDistance() {
	return frontDistances[2];
}

float GetBackDistance() {
	return backDistance;
}

void TestingDistanceAndAccuracy() {
	// Print distance readings for testing
	printf("Left Distance: %f cm\n", frontDistances[0]);
	printf("Center Distance: %f cm\n", frontDistances[1]);
	printf("Right Distance: %f cm\n", frontDistances[2]);
	printf("Back Distance: %f cm\n", backDistance);
}

void sonarDebug() {
	TestingDistanceAndAccuracy();
}
