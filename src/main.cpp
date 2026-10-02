#define STB_IMAGE_IMPLEMENTATION
#include "main.h"
#include "autons.hpp"
#include "buttons.hpp"
#include <filesystem>

#include <iostream>
#include <fstream>
#include <string>



void loadingScreenTask(){
    pros::delay(20);
    int time = 2000; // total time for loading screen in milliseconds
    std::string text = "1764P PARADOX";
    int timePerLetter = time / text.size();
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);
    
    pros::screen::set_eraser(0x151570);
    pros::screen::set_pen(0xffffff);
    for (size_t i = 0; i < text.size(); i++){
        pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 120, 100, text.substr(0, i+1).c_str());
        pros::delay(timePerLetter);
    }

    pros::delay(20);
}

 

void cycleChasingRainbow(pros::adi::Led *leftStrip, pros::adi::Led *rightStrip) {
    // code to cycle through the rainbow colors on the led strip
    static float hue = 0.0f;
    hue += 1; // Increment hue to cycle through colors
    if (hue >= 360) hue -= 360; // Wrap hue around at 360

    for (int i = 0; i < leftStrip->length(); i++) {
        // Calculate color based on hue and position in the strip
        float t = (float)i / leftStrip->length();
        float r = 0, g = 0, b = 0;

        float c = 1 * 1;              // Chroma
        float x = c * (1 - std::fabs(fmod((hue + i * (180 / leftStrip->length())) / 60.0f, 2) - 1));
        float m = 1 - c;

        float currentHue = hue + i * (180 / leftStrip->length());
        if (currentHue >= 360) currentHue -= 360;

        if (currentHue >= 0 && currentHue < 60) {
            r = c; g = x; b = 0;
        }
        else if (currentHue >= 60 && currentHue < 120) {
            r = x; g = c; b = 0;
        }
        else if (currentHue >= 120 && currentHue < 180) {
            r = 0; g = c; b = x;
        }
        else if (currentHue >= 180 && currentHue < 240) {
            r = 0; g = x; b = c;
        }
        else if (currentHue >= 240 && currentHue < 300) {
            r = x; g = 0; b = c;
        }
        else { // 300 - 360
            r = c; g = 0; b = x;
        }

        // printf("Hue: %f\n", currentHue);
        leftStrip->set_pixel((int)(r * 255) << 16 | (int)(g * 255) << 8 | (int)(b * 255), i);
    }
    for (int i = 0; i < rightStrip->length(); i++) {
        // Calculate color based on hue and position in the strip
        float t = (float)i / rightStrip->length();
        float r = 0, g = 0, b = 0;

        float c = 1 * 1;              // Chroma
        float x = c * (1 - std::fabs(fmod((hue + i * (180 / rightStrip->length())) / 60.0f, 2) - 1));
        float m = 1 - c;

        float currentHue = 180 + hue + i * (180 / rightStrip->length());
        if (currentHue >= 360) currentHue -= 360;

        if (currentHue >= 0 && currentHue < 60) {
            r = c; g = x; b = 0;
        }
        else if (currentHue >= 60 && currentHue < 120) {
            r = x; g = c; b = 0;
        }
        else if (currentHue >= 120 && currentHue < 180) {
            r = 0; g = c; b = x;
        }
        else if (currentHue >= 180 && currentHue < 240) {
            r = 0; g = x; b = c;
        }
        else if (currentHue >= 240 && currentHue < 300) {
            r = x; g = 0; b = c;
        }
        else { // 300 - 360
            r = c; g = 0; b = x;
        }
        // printf("Hue: %f\n", currentHue);
        rightStrip->set_pixel((int)(r * 255) << 16 | (int)(g * 255) << 8 | (int)(b * 255), rightStrip->length() - 1 - i);
    }

}
void LightsTask(){
    float a;
    float b;
    while (true){
        switch (colorMode) {
            case 'S':
                // printf("solid mode\n");
                // solid mode, do nothing
                if (currentTeam == 'R') {
                    leftLEDStrip.set_all(0xFF0000); // set all leds to red
                    rightLEDStrip.set_all(0xFF0000); // set all leds to red
                } else if (currentTeam == 'B') {
                    leftLEDStrip.set_all(0x0000FF); // set all leds to blue
                    rightLEDStrip.set_all(0x0000FF); // set all leds to blue
                } else {
                    leftLEDStrip.set_all(0xFFFFFF); // set all leds to white
                    rightLEDStrip.set_all(0xFFFFFF); // set all leds to white
                }
                break;
            case 'R':
                // printf("rainbow mode\n");
            
                cycleChasingRainbow(&leftLEDStrip, &rightLEDStrip);

                break;
            case 'W':
                // printf("wave mode\n");
                // wave mode, set each led to a color based on a sine wave
                a = 0.25;
                b = 12;
                for (int i = 0; i < leftLEDStrip.length(); i++) {
                    float t = pros::millis() / 1000.0 + (float)i / leftLEDStrip.length();
                    unsigned int color = 0xff * (a * sinf(b*t) + (1 - a));
                    if (currentTeam == 'R') {
                        color = color << 16; // shift red to the correct position
                    } else if (currentTeam == 'B') {
                        color = color; // blue is already in the correct position
                    } else {
                        // if team is neither, do white
                        color = (color << 16) | (color << 8) | color; // set all colors to the same value for white
                    }
                    // color = color << 16;
                    leftLEDStrip[i] = color;
                    rightLEDStrip[i] = color;
                }
                break;
            case 'C': // clipper mode white and blue circling the robot
                // use a sine wave and make all negative values blue and all positive values white
                // printf("clipper mode\n");
                b = 12;
                for (int i = 0; i < leftLEDStrip.length(); i++) {
                    float t = pros::millis() / 1000.0 + (float)i / leftLEDStrip.length();
                    unsigned int color = (sinf(b*t));
                    if (color > 0) {
                        color = (127 * color) << 16 | (127 * color) << 8 | (127 * color); // white
                    } else {
                        color = -127 * color; // blue
                    }
                    leftLEDStrip[i] = color;
                    rightLEDStrip[i] = color;
                }
                break;
        }
        leftLEDStrip.update();
        pros::delay(25);
        rightLEDStrip.update();
        pros::delay(25);
    }
}

void initialize() {
    pros::Task loadingScreen(loadingScreenTask);
	chassis.calibrate(true);
    

    pros::Task updateScreen(updateScreenTask);
    pros::Task lights(LightsTask);


    pros::screen::touch_callback(getTouched, pros::E_TOUCH_PRESSED);
    pros::screen::touch_callback(getTouched, pros::E_TOUCH_HELD);
    pros::screen::touch_callback(getTouched, pros::E_TOUCH_RELEASED);

}




/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    colorMode = 'C';
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    colorMode = 'C';
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	runAuton();
}



void opcontrol() {
    // driveToGoal(-50, true);
    while (true) {
        // Arcade control scheme
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX, true, 0.6);





        pros::delay(25); // Run for 20 ms then update
    }
}

//testing 33242342342