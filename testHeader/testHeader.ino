#include <time.h>
#include "testHeader.h"

const int ledOne = 8;
const int ledTwo = 9;
const int ledThree = 10;
const int ledFour = 11;

void setup(){
  setupInit(ledOne, ledTwo, ledThree, ledFour);
}

void loop(){
  blinkThrough();
}