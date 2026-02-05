#include "Weapon.h" //weapon.h is an interface essentially
#include <iostream>
#include <string>

void Weapon::init() {
  ESC_weaponUART.begin(ESC_BAUD);
}

int Weapon::constrainSpeed(int value) {
  return constrain(value, kMinSpeed, kMaxSpeed); //speed clamp
}

int Weapon::rampTo(int current, int target) { //math that gives us a smooth transition between throttle input and speed
  if (current < target) {
    current += kRampConstant;
    if (current > target) current = target;
  } 
  else if (current > target) {
    current -= kRampConstant;
    if (current < target) current = target;
  }
  return current; //lowk copied this func from github
}

void Weapon::sendToAM32(int motorID, int speed, String name) {//void means it returns nothing, we take in 2 params for motorID and speed.
  uint8_t packet[4] = { //unsigned 8bit intager array called packet
    (uint8_t)0xAA, //c++'s start byte telling the esc that the command is starting basically
    (uint8_t)motorID, //his tells the esp which motor should listen
    (uint8_t)(speed >> 8), //bit shifting by 8 bits. the UART can only handle 16 bits, so we split the 16bit int for SPEED into 2 8bit binary values. this holds the upper half
    (uint8_t)(speed &0xFF)// we now send the lower 8 bits of the speed. we basically butchered the shit out of the speed intager because the AM32 is a little bitch
  };
  ESC_weaponUART.write(packet, 4); //print() is human readable while write() is raw binary so it pushes everything to the UART.. packet is the array and 4 is the number of bytes to send
  //logging
  std::cout << "sent to am32: " + name + ", motor id: " + motorID + ", speed: " + speed;
}

void Weapon::setSpeed(int speed) { //same as like public Command setVoltageC() in frc programming... but with speed
  int target = constrainSpeed(speed); //sets target
  currentSpeed = rampTo(currentSpeed, target); //sets speed and lerps
  sendToAM32(kWeaponMotorID, currentSpeed, "Weapon input"); //sends informaiton to the UART
  std::cout << "set weapon speed to: " + speed;
}
