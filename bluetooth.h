#ifndef bluetooth_H
#define bluetooth_H

#include <SoftwareSerial.h>
#include "MotorModule.h"

void bluetooth(int speedBT, int directionTurnBT, int directionForwBackBT);
void initBluetooth();
#endif