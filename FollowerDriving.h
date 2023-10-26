#ifndef FollowerDriving_H
#define FollowerDriving_H
#include <Arduino.h>
#include "Driving.h"

void initFollower();
void runFollower(int speed);
int getFollowerSpeed();

#endif