#include <Arduino.h>
#include <time.h>

int _ledOne, _ledTwo, _ledThree, _ledFour;

void setupInit(int ledOne, int ledTwo, int ledThree, int ledFour){
  _ledOne = ledOne;
  _ledTwo = ledTwo;
  _ledThree = ledThree;
  _ledFour = ledFour;

  pinMode(_ledOne, OUTPUT);
  pinMode(_ledTwo, OUTPUT);
  pinMode(_ledThree, OUTPUT);
  pinMode(_ledFour, OUTPUT);

  digitalWrite(_ledOne, LOW);
  digitalWrite(_ledTwo, LOW);
  digitalWrite(_ledThree, LOW);
  digitalWrite(_ledFour, LOW);
}

void blinkThrough(){
  digitalWrite(_ledOne, HIGH);
  delay(100);
  digitalWrite(_ledOne, LOW);

  digitalWrite(_ledTwo, HIGH);
  delay(100);
  digitalWrite(_ledTwo, LOW);

  digitalWrite(_ledThree, HIGH);
  delay(100);
  digitalWrite(_ledThree, LOW);

  digitalWrite(_ledFour, HIGH);
  delay(100);
  digitalWrite(_ledFour, LOW);
}