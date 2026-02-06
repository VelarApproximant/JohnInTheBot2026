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

inline int constrain(int val, int minVal, int maxVal) {
    if (val < minVal) return minVal;
    if (val > maxVal) return maxVal;
    return val;
}

inline int map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) /
           (in_max - in_min) + out_min;
}

// ---- Simulated HardwareSerial ----
class HardwareSerial {
public:
    void begin(int baud) {
        std::cout << "serial begin at " << baud << " baud\n";
    }

    void write(const uint8_t* data, size_t len) {
        std::cout << "uart Packet: ";
        for (size_t i = 0; i < len; i++) {
            std::cout << std::hex << (int)data[i] << " ";
        }
        std::cout << std::dec << "\n";
    }
};

// These exist just like on Arduino
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
