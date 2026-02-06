#ifndef ROBOT_CONTAINER_H
#define ROBOT_CONTAINER_H

#include <Arduino.h>
#include "sbus.h"
#include "../Constants.h"
#include "../Drivetrain/Drivetrain.h"
#include "../Subsystem/Weapon.h"

using namespace bfs;//same as java static import

class RobotContainer {
public:
    RobotContainer(); //java's interface logic where it declares what methods and constructor must exist in the cpp file
    void init();
    void periodic();

private:
    SbusRx sbus; 
    Drivetrain drivetrain;
    Weapon weapon;
    /* 
    same as java's:
    private SbusRx sbus;
    private Drivetrain drivetrain = new Drivetrain();
    private Weapon weapon = new Weapon();
    */

    int throttle = 1500; //neutral speed variables as 1500 is the neutral state.
    int steering = 1500;
    int weaponChannel = 1500;

    int mapSbusToSpeed(int sbusValue); //declares there must be a mapSbusToSpeed method in the cpp file
};

#endif
