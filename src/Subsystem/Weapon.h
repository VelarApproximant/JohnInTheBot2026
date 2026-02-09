#ifndef WEAPON_H
#define WEAPON_H

#include <Arduino.h>
#include "../Constants.h"
#include <string>

class Weapon {
  public:
    void init(); //method declarations
    void setSpeed(int speed);

  private:
    int currentSpeed = 1500; //I set the basic speed of the weapon to idle at a no speed

    int manualPID(int current, int target);
    int constrainSpeed(int value);
    void sendToESC(int motorID, int speed, String name);
};

#endif
