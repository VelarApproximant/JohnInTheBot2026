#include "Weapon.h"
#include <iostream>
#include <string>

void Weapon::init() {
  kSpinnerUART.begin(ESC_BAUD);
}

int Weapon::constrainSpeed(int value) {
  return constrain(value, kMinSpeed, kMaxSpeed); 
}

int Weapon::manualPID(int currentSpeed, int targetSpeed) {
  if (currentSpeed < targetSpeed) {
    currentSpeed = currentSpeed + kRampConstant;
    if (currentSpeed > targetSpeed) currentSpeed = targetSpeed;
  } 
  else if (currentSpeed > targetSpeed) {
    currentSpeed -= kRampConstant;
    if (currentSpeed < targetSpeed) currentSpeed = targetSpeed;
  }
  return currentSpeed; 
}
void Weapon::sendToESC(int motorID, int speed, String name) {
  uint8_t packet[4] = {
    (uint8_t)0xAA,
    (uint8_t)motorID,
    (uint8_t)(speed >> 8), 
    (uint8_t)(speed &0xFF)
  };
  kSpinnerUART.write(packet, 4); 
  //logging
  std::cout << "sent to am32: " << name << ", motor id: " << motorID << ", speed: " << speed;
}

void Weapon::setSpeed(int speed) { 
  currentSpeed = manualPID(currentSpeed, speed); 
  sendToESC(kSpinnerMotorID, currentSpeed, "Weapon input");
  std::cout << "set weapon speed to: " << speed;
}
