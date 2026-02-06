
// RobotContainerSim.cpp
#include "RobotContainerSim.h"
#include "simUtil.h"

void RobotContainerSim::init() {
    drivetrain.init();
    weapon.init();
}

int RobotContainerSim::mapSbusToSpeed(int sbusValue) {
    return map(sbusValue, 0, 2047, 1000, 2000);
}

void RobotContainerSim::periodic(int throttleInput,
                                 int steeringInput,
                                 int weaponInput,
                                 bool invertPressed) {

    int throttle = mapSbusToSpeed(throttleInput);
    int steering = mapSbusToSpeed(steeringInput);
    int weaponSpeed = mapSbusToSpeed(weaponInput);

    drivetrain.tankDrive(throttle, steering, invertPressed);
    weapon.setSpeed(weaponSpeed);
}
