#include "Drivetrain.h"

void Drivetrain::init() {
  ESC_leftUART.begin(ESC_BAUD); //init for both motor UART
  ESC_rightUART.begin(ESC_BAUD);
}

int Drivetrain::constrainSpeed(int value) {
  return constrain(value, kMinSpeed, kMaxSpeed); //sets speed clamp
}

int Drivetrain::rampTo(int current, int target) { 
  if (current < target) { //TODO: change current and target to currentSpeed and targetSpeed
    current += kRampConstant;
    if (current > target) current = target;
  } 
  else if (current > target) {
    current -= kRampConstant;
    if (current < target) current = target;
  }
  return current; 
}

void Drivetrain::sendToAM32(HardwareSerial &uart, int motorID, int speed) {
  uint8_t packet[4] = { 
    0xAA,
    (uint8_t)motorID,
    (uint8_t)(speed >> 8),
    (uint8_t)(speed & 0xFF)
  };
  uart.write(packet, 4); 
}

void Drivetrain::tankDrive(int throttle, int steering, bool buttonPressed) {
  //toggle (Detects the moment the button is pressed)
  if (buttonPressed && !lastButtonState) { 
    steeringInverted = !steeringInverted; // switches the state
  }
  lastButtonState = buttonPressed; //save this state for next loop

  //inverts Steering if toggled
  int steeringOffset = (steering - 1500); //calculates how far stick is pushed as 1500 is neutral pos
  if (steeringInverted) {
    steeringOffset = -steeringOffset; // flip the direction
  }

  //clamps speeds so AM32 doesnt get confused
  int targetLeft  = constrainSpeed(throttle + steeringOffset);
  int targetRight = constrainSpeed(throttle - steeringOffset);

  currentLeft = rampTo(currentLeft, targetLeft); //smooth accel
  currentRight = rampTo(currentRight, targetRight);

  sendToAM32(ESC_leftUART, kLeftMotorID, currentLeft); //sends data to AM32
  sendToAM32(ESC_rightUART, kRightMotorID, currentRight);
}

