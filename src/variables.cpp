#include "variables.hpp"

// Motor groups - 5, 6, 7, 8, 9, 10
pros::MotorGroup ldrive({ -13, -12}, pros::v5::MotorGears::blue);
pros::MotorGroup rdrive({19, 20}, pros::v5::MotorGears::blue);

// Inertial sensor
pros::Imu imu(17);

// Drivetrain configuration
lemlib::Drivetrain drivetrain(&ldrive, // left motor group
                              &rdrive, // right motor group
                              9.25, // 9.25 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 2.75" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

// Left tracking wheel
lemlib::TrackingWheel left_tracking(
	&ldrive, //Look at the left drive
	2.75, //2.75 inch wheels
	-4.125, //6.2875 incheas left of the center
	450  //Max RPM of 450
);

// Right tracking wheel
lemlib::TrackingWheel right_tracking(
	&rdrive, //Look at the left drive
	2.75, //2.75 inch wheels
    4.125, //6.2875 incheas right of the center
	450 //Max RPM of 450
);

// Odometry sensors
lemlib::OdomSensors sensors(&left_tracking, // vertical tracking wheel 1, set to null
                            &right_tracking, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

//8 0 16.  2:53 jan 10
// Lateral PID controller
// last pid was 8.7, 0, 37
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              96, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              300, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
//2.6, 0, 19 = ~0.5 off consistent and snappy
// Angular PID controller
lemlib::ControllerSettings angular_controller(2.46, // proportional gain (kP)
                                              0.5, // integral gain (kI)
                                              18, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              5, // large error range, in degrees
                                              300, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// Throttle drive curve
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1 // expo curve gain
);

// Steer drive curve
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1 // expo curve gain
);

// Chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors, // odometry sensors
                        &throttle_curve, 
                        &steer_curve
);


// Game state variables
int currentAuton = 2; // will only be changed in buttons.cpp
char currentTeam = 'R'; // 'R' or 'B'
char currentSide = 'L'; // 'R' or 'L'
char colorMode = 'S';     // 'S', 'W', 'C', or 'R'
bool holdingOpponent = false;

// Controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);


pros::adi::Led leftLEDStrip('d', 20);
pros::adi::Led rightLEDStrip('e', 20);


// UI scene system
Scene currentScene = {nullptr, nullptr};

bool updateScreen = true;
int updateDelay = 50;
int scoringSpeed = 127;

std::array<float, 150> graph;
std::array<float, 150> power;