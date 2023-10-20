#include "IRModule.h"

bool readingIRF, readingIRL, readingIRR;

#define IRFront 5
#define IRLeft 6
#define IRRight 7

bool debug = true;

void setup(){
  Serial.begin(9600);
  initIRModule(IRFront, IRLeft, IRRight);
}  

void loop(){
  if(debug){
    IRDebug();
  }
}