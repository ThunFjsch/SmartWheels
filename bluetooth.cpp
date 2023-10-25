#include <SoftwareSerial.h>
#include "motormodule.h"

// BT pin definition
#define btRXD 12
#define btTXD 13 


//setting up communication with the bt chip
SoftwareSerial mySerial(btRXD,btTXD);



void bluetooth() {//function that makes bluetooth usable
  
  char message;
  while(mySerial.available()){
    message = mySerial.read();  

    switch(message){//checks input message
            case '0'://steers left
              steerLeftSimple(speed);
              directionTurn = 1;
              break;
            case '1'://steers right
              steerRightSimple(speed);
              directionTurn = 1;
              break;
            case '2'://forward
              directionForwBack = true;
              setMotorDirection(true);
              break;
            case '3': //reverse
              directionForwBack = false;
              setMotorDirection(false);
              break;
            case '4'://increase speed to 255 max
              speed += 20;
              directionTurn = 0;
              if(speed > 255){
                speed = 255;
              }
              setAllMotorSpeed(speed);
              break;
            case '5'://decrease speed untill 0
              speed -= 20;
              directionTurn = 0;
              if(speed < 0){
                speed = 0;
              }
              setAllMotorSpeed(speed);
              break;
            case '6'://stops all motors
              stopMotors();
              speed = 0;
              break;
    }//end of switch case   
  }
}