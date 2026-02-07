// DrivetrainSim.h
#pragma once
#include "../Util/SimUtil.h" 
#include "../src/Constants.h"

class DrivetrainSim {
public:
    void init();
    void tankDrive(int throttle, int steering, bool buttonPressed);

private:
    int currentLeft = 1500;
    int currentRight = 1500;

    bool steeringInverted = false;
    bool lastButtonState = false;

    int rampTo(int current, int target);
    int constrainSpeed(int value);
    void sendToAM32(HardwareSerial& uart, int motorID, int speed, String name);
};