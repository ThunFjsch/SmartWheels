#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

#include "HCSR04.h"

// files have been included from this repo: https://github.com/MUDAL/Ultrasonic-Sensor-Driver
// little stuff changed to play around with it.

uint32_t distance;

int main(){

	HCSR04_Init();
	while (1){
		uint32_t distance = getDistance();
	}
	
}