#include <iostream>
#include "RobotSim/RobotContainerSim.h"
#include "../src/Constants.h"

int main() {
    RobotContainerSim robot;
    robot.init();

    std::cout << "simulation start\n";

    // Fake SBUS inputs (0–2047 range)
    int throttle = 1024;
    int steering = 1024;
    int weapon = 1024;
    bool invert = false;

    for (int i = 0; i < 20; i++) {
        std::cout << "\n cycle number: " << i << "\n";

        // Slowly ramp inputs for testing
        throttle += 50;
        steering += (i % 2 == 0) ? 30 : -30;
        weapon += 40;

        robot.periodic(throttle, steering, weapon, invert);

        delay(20);
    }

    std::cout << "finish\n";
    return 0;
}
