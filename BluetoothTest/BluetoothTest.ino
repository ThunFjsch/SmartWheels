#include <SoftwareSerial.h>

SoftwareSerial HM10(12, 13); // TX = 2, RX = 3

char appData;  

int inData = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
}


void loop()

{

  HM10.listen();  // listen the HM10 port

  while (HM10.available() > 0) {   // if HM10 sends something then read

    appData = HM10.read();

    inData = appData;  // save the data in string format

    Serial.write(appData);

  }

  if (Serial.available()) {           // Read user input if available.

    delay(10);

    HM10.write(Serial.read());

  }

    switch(inData)                                              //compares input to cases and executes code within case
    {
        case 0:
              Serial.println("mode ++");
              break;
        case 1:
              Serial.println("left");
              break;
        case 2:
              Serial.println("forward");
              break;
        case 3:
              Serial.println("right");
              break;
        case 4:
              Serial.println("reverse");
              break;
        case 5:
              Serial.println("reset movement");
              break;
    }
}