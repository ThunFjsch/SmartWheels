#include "OLEDScreen.h"
#define modeSwitchButton 6

bool directionGasReverse = true; // Forward
bool directionTurn = true; // Left

void setup(void)
{
  initIOModule(modeSwitchButton, directionGasReverse, directionTurn, true);
}

void loop(void)
{
  showTime();
  timeSave();
  drawDisplayBitmaps();
}


