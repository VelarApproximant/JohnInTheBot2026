#include "RobotContainer.h" //#include is the same as a java import
#include "sbus.h" //sbus is a serial bus that connects this to the transmitter

RobotContainer::RobotContainer() //cpp version of a constructor; "::" refers to a method in a class (in robotContainer.h)

#if defined(ESP32) //tells compiler to only make the sbus if we are using an ESP32 (IDK WHY BUT THIS KILLS ALL ERRORS FOR ME)
  : sbus(&Serial1, 16, 17, true) //creates new sbus object with those port numbers. true is to invert the sbus protocol (they told me to put it)
#endif //end if statement
{} //body of constructor is empty bc nothings inside curlly braces

void RobotContainer::init() {
    Serial.begin(ESC_BAUD); //opens baus at 100000 baud
    Serial1.begin(ESC_BAUD); // Pick any 2 free pins for TX/RX
    Serial2.begin(ESC_BAUD); // Default Serial2 pins
    
    sbus.Begin(); //sbus lib starts listening for input
    drivetrain.init(); 
    weapon.init();
}

int RobotContainer::mapSbusToSpeed(int sbusValue) {
    return map(sbusValue, 0, 2047, 1000, 2000); //helpful arduino method i can explain later bc its long
}

void RobotContainer::periodic() {
    bool invertPressed = false; //is the invert button pressed?

    bool downforceKill = false;
    bool lastKillState = false;
    int downforceSpeed = 2000;

    if (sbus.Read()) {
        auto data = sbus.data();

        throttle = mapSbusToSpeed(data.ch[kThrottleChannel - 1]);
        steering = mapSbusToSpeed(data.ch[kSteeringChannel - 1]);

        weaponChannel = mapSbusToSpeed(data.ch[kWeaponChannel - 1]);

        // READ THE INVERT BUTTON using channel 5 as an example
        // SBUS values are usually ~172 for LOW and ~1811 for HIGH
        invertPressed = (data.ch[kInvertChannel - 1] > 1500); 

        bool currentButtonState = (data.ch[kDownforceMotorChannel - 1] > 1500);

        // if (currentButtonState && !lastKillButtonState) {
        //     isMotorDisabled = !isMotorDisabled; // Flip the state
        // }
        // lastKillButtonState = currentButtonState;
    }

    // pass the button state to tankDrive method
    drivetrain.tankDrive(throttle, steering, invertPressed); 
    weapon.setSpeed(weaponChannel);
}

