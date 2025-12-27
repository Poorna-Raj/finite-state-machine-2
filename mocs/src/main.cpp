#include <Arduino.h>
#include "SystemManager.h"

LED stateLED(2, 200);
LED diagLED(3, 200);

Button modeButton(6);
Button resetButton(7);

SystemManager manager(&modeButton, &resetButton, &stateLED, &diagLED);

void setup()
{
  manager.begin();
}

void loop()
{
  manager.update();
}