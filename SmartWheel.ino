#include <SoftwareSerial.h>                                //defining RXD and TXD pin to D12 & D13
#define btTXD 12                                             
#define btRXD 13                                             

SoftwareSerial mySerial(btTXD,btRXD);                      //setting up communication with the chip

void setup()                                               //starting communication with the bt chip
{
  mySerial.begin(9600);                                    
}

void loop()
{
  int i;
   
  if (mySerial.available())                                //checks if there is communication
  {
    i=mySerial.read();
    
    //Serial.println("DATA RECEIVED:");                    //uncomment to check if communication is working
    
    switch(i)                                              //compares input to cases and executes code within case
    {
        case '0':
               Serial.println("mode ++");
              break;
        case '1':
              Serial.println("left");
              break;
        case '2':
              Serial.println("forward");
              break;
        case '3':
              Serial.println("right");
              break;
        case '4':
              Serial.println("reverse");
              break;
        case '5':
              Serial.println("reset movement");
              break;
    }
  }
}
