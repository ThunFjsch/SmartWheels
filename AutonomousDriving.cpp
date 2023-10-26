#include "AutonomousDriving.h"

void runAutonomous(int speed){
    collisionAvoidanceSpeedControl(speed);
    lineSteeringBehaviour(speed);
}

int getAutonomSpeed(){
    return getDrivingSpeed();
}