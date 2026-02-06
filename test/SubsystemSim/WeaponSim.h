// WeaponSim.h
#pragma once
#include "../Util/SimUtil.h"
#include "../src/Constants.h"

class WeaponSim {
public:
    void init();
    void setSpeed(int speed);

private:
    int currentSpeed = 1500;

    int rampTo(int current, int target);
    int constrainSpeed(int value);
    void sendToAM32(int motorID, int speed, String name);
};
