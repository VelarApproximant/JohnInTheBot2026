#ifndef CONSTANTS_H
#define CONSTANTS_H

// Pin numbers and uart
#define SBUS_recieverPin 4 //connect the SBUS signal wire here
#define SBUS_UART Serial

#define ESC_SpinnerUART Serial1
#define ESC_leftUART Serial1
#define ESC_rightUART Serial2

#define ESC_BAUD 115200 //BAUD rate in bits per second (bps)

// motor id
#define kLeftMotorID 1 //TODO: find real values
#define kRightMotorID 2
#define kSpinnerMotorID 3

// channel port
#define kThrottleChannel 1 //TODO: tune to preference
#define kSteeringChannel 2
#define kSpinnerChannel 3
#define kInvertDrivetrainChannel 4

// speed limiters (1000 is full reverse and 2000 is full forward when set to bidirectional)
#define kMinSpeed 1000
#define kMaxSpeed 2000

// we should change ts constant because it may be too smooth
#define kRampConstant 10

// loop delay
#define loopDelayInMS 20

#endif

