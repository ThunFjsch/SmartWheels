#include "Driving.h"
#include "SonarModule.h"

int followerDistanceRangeMin;
int followerDistanceRangeMax;

void initFollower(int _followerDistanceRangeMin, int _followerDistanceRangeMax){
    followerDistanceRangeMin = _followerDistanceRangeMin;
    followerDistanceRangeMax = _followerDistanceRangeMax;
    isOnLine();
}

void runFollower(){
    if(!isSomethingInRange(followerDistanceRangeMin, followerDistanceRangeMax)){
        correctRangeChange();   // correct the speed of the car to align within the range
    }
    lineSteeringBehaviour();
}