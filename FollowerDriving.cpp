#include "Driving.h"
#include "SonarModule.h"

int followerDistanceRangeMin;
int followerDistanceRangeMax;

void initFollower(int _followerDistanceRangeMin, int _followerDistanceRangeMax){
    followerDistanceRangeMin = _followerDistanceRangeMin;
    followerDistanceRangeMax = _followerDistanceRangeMax;
    isOnLine();
}

void runFollower(int speed){
    if(!isSomethingInRange(followerDistanceRangeMin, followerDistanceRangeMax)){
        correctRangeChange(speed);   // correct the speed of the car to align within the range
    }
    lineSteeringBehaviour(speed);
}

int getFollowerSpeed(){
    return getDrivingSpeed();
}