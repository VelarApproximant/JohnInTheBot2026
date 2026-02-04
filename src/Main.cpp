#include <Arduino.h>
#include "Robot/RobotContainer.h"
#include "Constants.h"

RobotContainer robot; //instantiate object of RobotContainer

void setup() { //arduino's provided "initialization" function
  Serial.begin(115200); //opens USB serial port so you can see debug
  robot.init(); //calls all subsystem to init
}

void loop() { //runs every 20 ms and is defined by arduino
  robot.periodic(); //calls periodic method within RobotContainer.cpp
  delay(loopDelayInMS); //20 ms delay
}
