// WeaponSim.cpp
#include "WeaponSim.h"
#include <iostream>

void WeaponSim::init() {
    Serial1.begin(ESC_BAUD);
}

int WeaponSim::constrainSpeed(int value) {
    return constrain(value, kMinSpeed, kMaxSpeed);
}

int WeaponSim::rampTo(int current, int target) {
    if (current < target) {
        current += kRampConstant;
        if (current > target) current = target;
    } else if (current > target) {
        current -= kRampConstant;
        if (current < target) current = target;
    }
    return current;
}

void WeaponSim::sendToAM32(int motorID, int speed, String name) {
    std::cout << "sent command to am32: " << name << ", motor: " << motorID << ", with speed: " << speed << "\n";
}

void WeaponSim::setSpeed(int speed) {
    int target = constrainSpeed(speed);
    currentSpeed = rampTo(currentSpeed, target);
    sendToAM32(kSpinnerMotorID, currentSpeed, "set weapon speed");
}
