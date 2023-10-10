#include "OLEDScreen.h"
#define modeSwitchButton 6

bool direction = true;

void setup(void)
{
  initIOModule(modeSwitchButton, direction);
}

void loop(void)
{
  showTime();
  timeSave();
  drawDisplayBitmaps();
}


