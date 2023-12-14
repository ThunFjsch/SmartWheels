#define F_CPU 16000000;
#include <avr/io.h>
#include <avr/interrupt.h>

#include "HCSR04.h"

uint32_t distance;

int main(void){
	HCSR04_init();
	
  while (1) {
		distance = getDistance();
  }
}

