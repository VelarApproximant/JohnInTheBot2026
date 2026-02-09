#include "RobotContainer.h" //#include is the same as a java import
#include "sbus.h" //sbus is a serial bus that connects this to the transmitter

RobotContainer::RobotContainer()
#if defined(ESP32)
  : sbus(&Serial1, 16, 17, true)
#endif
{} 

void RobotContainer::init() {
    Serial.begin(DEF_BAUD);
    Serial1.begin(ESC_BAUD); 
    Serial2.begin(ESC_BAUD); 
    
    sbus.Begin(); //sbus lib starts listening for input
    drivetrain.init(); 
    weapon.init();
}

int RobotContainer::mapSBUSToSpeed(int sbusValue) {
    return map(sbusValue, 0, 2047, 1000, 2000); //helpful arduino method i can explain later bc its long
}

void RobotContainer::periodic() {
    bool invertDrivetrainPressed = false; //is the invert button pressed?

    // bool downforceKill = false;
    // bool lastKillState = false;
    // int downforceSpeed = 2000;

    if (sbus.Read()) {
        auto data = sbus.data();

        throttle = mapSBUSToSpeed(data.ch[kThrottleChannel - 1]);
        steering = mapSBUSToSpeed(data.ch[kSteeringChannel - 1]);

        weaponChannel = mapSBUSToSpeed(data.ch[kSpinnerChannel - 1]);

        // READ THE INVERT BUTTON using channel 5 as an example
        // SBUS values are usually ~172 for LOW and ~1811 for HIGH
        invertDrivetrainPressed = (data.ch[kInvertDrivetrainChannel - 1] > 1500); 

        // bool currentButtonState = (data.ch[kDownforceMotorChannel - 1] > 1500);

        // if (currentButtonState && !lastKillButtonState) {
        //     isMotorDisabled = !isMotorDisabled; // Flip the state
        // }
        // lastKillButtonState = currentButtonState;
    }

    // pass the button state to tankDrive method
    drivetrain.tankDrive(throttle, steering, invertDrivetrainPressed); 
    weapon.setSpeed(weaponChannel);
}

