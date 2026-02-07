// SimUtil.h
#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>
#include <string>

using String = std::string;

// ---- Arduino-like helpers ----
inline void delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline int constrain(int val, int minVal, int maxVal) { //a clamp; takes a value and clamps it between 2nd and 3rd param
    if (val < minVal) {
        return minVal
    };
    if (val > maxVal) {
        return maxVal
    };
    return val;
}

inline int map(int x, int in_min, int in_max, int out_min, int out_max) { //replicating arduino's map function
    return (x - in_min) * (out_max - out_min) /
           (in_max - in_min) + out_min;
}

// simulation for a serial bus as the sim is just c++ without any dev board
class HardwareSerial { //creates new class called HardwareSerial
public:
    HardwareSerial() {} //empty default constructor (this is automatically generated but I added one for expolaining)

    void begin(int baud) { //mimics how you would initialize an actual ESP board
        std::cout << "serial begin at " << baud << " baud\n"; //legit just prints that it begins
    }

    void write(uint8_t* data, size_t length) { //length should almost always be 4
        std::cout << "uart Packet: "; //print out "uart Packet"
        for (size_t i = 0; i < length; i++) { //loops through each byte and prints it in hexadecimal
            std::cout << std::hex << (int)data[i];
        }
        std::cout << std::dec; //switches the hexadecimal value back to normal deciaml numbers
    }
};

// extern means that there will be these variables defined elsewhere
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
