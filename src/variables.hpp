#pragma once
#include "lemlib/api.hpp"
#include "logger.hpp"

// Motor groups
extern pros::MotorGroup ldrive;
extern pros::MotorGroup rdrive;

// Sensors
extern pros::Imu imu;
extern lemlib::Drivetrain drivetrain;
extern lemlib::TrackingWheel left_tracking;
extern lemlib::TrackingWheel right_tracking;
extern lemlib::OdomSensors sensors;
extern pros::Rotation winch;


// PID controllers
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

// Drive curves
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;

// Chassis
extern lemlib::Chassis chassis;


// Controllers
extern pros::Controller master;
extern pros::Controller partner;


extern pros::adi::Led leftLEDStrip;
extern pros::adi::Led rightLEDStrip;


extern pros::adi::DigitalOut claw;
extern bool clawState;

// Intake motors
extern pros::Motor bottomIntake;
extern pros::Motor topIntake;

// Cascade
extern pros::MotorGroup cascade;

// Arm
extern pros::MotorGroup arm;

//Wrist
extern pros::Motor wrist;

extern bool updateScreen;
extern int updateDelay;
extern int scoringSpeed;

#pragma once
#include "main.h"

// Intake state
extern int intaking;
extern int lastIntaking;

// Alliance / side
extern char currentTeam;   // 'R' or 'B'
extern char currentSide;   // 'R' or 'B'
extern char colorMode;     // 'S', 'W', or 'R'
extern int currentAuton;

// Color sort
extern bool holdingOpponent;

struct Scene {
    void (*drawFunction)();
    void (*touchFunction)(pros::screen_touch_status_s_t status);
};

extern Scene currentScene;

ASSET(Logo1764P_png);
ASSET(homeIcon_png);
ASSET(drivetrain_png);
ASSET(PID_png);
ASSET(Graph_png);

extern std::array<float, 150> graph;
extern std::array<float, 150> power;

extern int winchTarget;
extern int lastWinchTarget;
extern int upHeight;
extern int midHeight;
extern int downHeight;
extern int maxWinchUp;
extern int maxWinchDown;

extern int armTarget;
extern int armDownHeight;
extern int armUpHeight;

extern int wristTarget;
extern int wristDownHeight;
extern int wristUpHeight;
extern int wristHoldingHeight;

extern int maxArmDown;
extern int maxArmUp;
extern int currentArmMax;

extern int maxWristDown;
extern int maxWristUp;
extern int currentWristMax;

enum ScoringState {
    HIGHHIGH,
    LOWHIGH,
    MIDMID,
    GOINGDOWN,
    NORMAL,
    DRIVING
};

extern ScoringState scoringState;