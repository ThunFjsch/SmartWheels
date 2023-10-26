#include <SoftwareSerial.h>
#include "MotorModule.h"

// BT pin definition
#define btRXD 12
#define btTXD 13 

//setting up communication with the bt chip
SoftwareSerial mySerial(btRXD,btTXD);

void initBluetooth(){
  mySerial.begin(9200);
}

void bluetooth(int speedBT, int directionTurnBT, int directionForwBackBT) {//function that makes bluetooth usable
  char message;
  while(mySerial.available()){
    message = mySerial.read();  

    switch(message){//checks input message
            case '0'://steers left
              steerLeftSimple(speedBT);
              directionTurnBT = 1;
              break;
            case '1'://steers right
              steerRightSimple(speedBT);
              directionTurnBT = 1;
              break;
            case '2'://forward
              directionForwBackBT = true;
              setMotorDirection(true);
              break;
            case '3': //reverse
              directionForwBackBT = false;
              setMotorDirection(false);
              break;
            case '4'://increase speedBT to 255 max
              speedBT += 20;
              directionTurnBT = 0;
              if(speedBT > 255){
                speedBT = 255;
              }
              setAllMotorSpeed(speedBT);
              break;
            case '5'://decrease speedBT untill 0
              speedBT -= 20;
              directionTurnBT = 0;
              if(speedBT < 0){
                speedBT = 0;
              }
              setAllMotorSpeed(speedBT);
              break;
            case '6'://stops all motors
              stopMotors();
              speedBT = 0;
              break;
    }//end of switch case   
  }
}