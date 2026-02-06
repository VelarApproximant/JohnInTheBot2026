// RobotContainerSim.h
#pragma once
#include "../DrivetrainSim/DrivetrainSim.h"
#include "../SubsystemSim/WeaponSim.h"

class RobotContainerSim {
public:
    void init();
    void periodic(int throttleInput,
                  int steeringInput,
                  int weaponInput,
                  bool invertPressed);

private:
    DrivetrainSim drivetrain;
    WeaponSim weapon;

    int mapSbusToSpeed(int sbusValue);
};
