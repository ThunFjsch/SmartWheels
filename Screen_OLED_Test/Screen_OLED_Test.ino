#include "OLEDScreen.h"

//7.5 hours; reading library documentation and understanding

void setup(void)
{
  initIOModule();
}

void loop(void)
{
  checkTime();
  showTime();
  timeSave();
  elements();
  increaseSeconds();
}


