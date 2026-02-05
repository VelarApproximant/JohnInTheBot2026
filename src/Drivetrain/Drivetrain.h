#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Arduino.h>
#include "../Constants.h"
#include <string>

class Drivetrain {
  public:
    void init(); //declares that these methods must exist
    void tankDrive(int throttle, int steering, bool buttonPressed);

  private:
    int currentLeft = 1500; //neutral values
    int currentRight = 1500;

    bool steeringInverted = false; //toggle logic for steering inversion
    bool lastButtonState = false;


    int rampTo(int current, int target);
    int constrainSpeed(int value);
    void sendToAM32(HardwareSerial &uart, int motorID, int speed, String name);
};

#endif
