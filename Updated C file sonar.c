// SonarModule.cpp
#include "SonarModule.h"

int trigPin, echoPinBack, echoPinCenter, echoPinLeft, echoPinRight;
float backDistance = 0;
float frontDistances[3];

void initSonarModule(int _trigPin, int _echoPinBack, int _echoPinCenter, int _echoPinLeft, int _echoPinRight) {
	// Sets the given PinLayout to global variables
	trigPin = _trigPin;
	echoPinBack = _echoPinBack;
	echoPinCenter = _echoPinCenter;
	echoPinLeft = _echoPinLeft;
	echoPinRight = _echoPinRight;

	// Setup Sonar Pins
	pinMode(trigPin, OUTPUT);
	pinMode(echoPinBack, INPUT);
	pinMode(echoPinCenter, INPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(echoPinRight, INPUT);
}

void updatedSonarDistance() {
	// Updating sonar hardware
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10); // Adjust this delay as needed
	digitalWrite(trigPin, LOW);

	// Calculation to convert the reading from the sonar sensor into centimeters
	float distanceCalc = 0.034 / 2; // Speed of sound in air divided by 2 (distance in cm per microsecond)
	
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
	Serial.println("Left Distance: " + String(frontDistances[0]) + " cm");
	Serial.println("Center Distance: " + String(frontDistances[1]) + " cm");
	Serial.println("Right Distance: " + String(frontDistances[2]) + " cm");
	Serial.println("Back Distance: " + String(backDistance) + " cm");
}

void sonarDebug() {
	TestingDistanceAndAccuracy();
}


