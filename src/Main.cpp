#include <Arduino.h>
#include "Robot/RobotContainer.h"
#include "Constants.h"

RobotContainer robot; // construcytor instantiAate

void setup() { 
  Serial.begin(DEF_BAUD); //1200 baud for now
  robot.init(); 
}

void loop() { 
  robot.periodic(); 
  delay(loopDelayInMS); 
}
