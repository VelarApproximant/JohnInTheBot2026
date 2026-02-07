// DrivetrainSim.cpp
#include "DrivetrainSim.h"
#include <iostream>

void DrivetrainSim::init() {
    Serial1.begin(ESC_BAUD);
    Serial2.begin(ESC_BAUD);
}

int DrivetrainSim::constrainSpeed(int speed) {
    return constrain(speed, kMinSpeed, kMaxSpeed);
}

int DrivetrainSim::rampTo(int current, int target) {
    if (current < target) {
        current += kRampConstant;
        if (current > target) current = target;
    } else if (current > target) {
        current -= kRampConstant;
        if (current < target) current = target;
    }
    return current;
}

void DrivetrainSim::sendToAM32(HardwareSerial&, int motorID, int speed, String name) {
    std::cout << "sent command to am32: " << name << ", motor: " << motorID << ", with speed: " << speed << "\n";
}

void DrivetrainSim::tankDrive(int throttle, int steering, bool buttonPressed) {
    if (buttonPressed && !lastButtonState) {
        steeringInverted = !steeringInverted;
        std::cout << "steering inverted: "
                  << steeringInverted << "\n";
    }
    lastButtonState = buttonPressed;

    int steeringOffset = steering - 1500;
    if (steeringInverted) steeringOffset = -steeringOffset;

    int targetLeft  = constrainSpeed(throttle + steeringOffset);
    int targetRight = constrainSpeed(throttle - steeringOffset);

    currentLeft  = rampTo(currentLeft, targetLeft);
    currentRight = rampTo(currentRight, targetRight);

    sendToAM32(Serial1, kLeftMotorID, currentLeft, "set left drive");
    sendToAM32(Serial2, kRightMotorID, currentRight, "set right drive");
}
