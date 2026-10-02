#pragma once
#include "../../drawing.hpp"


extern Scene DrivetrainFrictionScreenScene;

extern Scene HomeScreenScene;

inline void drawDrivetrainFrictionScreen(){
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);

    drawAsset(homeIcon_png, 5, 5, 50, 50);

    pros::screen::set_pen(0xffffff);
    pros::screen::set_eraser(0x151570);
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 30, 70, "Left");
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 140, 70, "Right");

    for (int i = 0; i < 3; i++){
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 30, 100 + i*13, "[%d]: %.2fW", ldrive.get_port(i), ldrive.get_power(i));
        // pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 30, 100 + i*10, "[%d]: %.2fW", ldrive.get_port(i), ldrive.get_power()[i]);
    }

    for (int i = 0; i < 3; i++){
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 140, 100 + i*13, "[%d]: %.2fW", rdrive.get_port(i), rdrive.get_power(i));
        // pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 120, 100 + i*10, "[%d]: %.2fW", rdrive.get_port(i), rdrive.get_power()[i]);
    }


    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 30, 150, "Intake");

    // pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 30, 180, "[%d]: %.2fW", topIntake.get_port(), topIntake.get_power());
    // pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 30, 180 + 13, "[%d]: %.2fW", bottomIntake.get_port(), bottomIntake.get_power());

    updateScreen = true;
}

inline void touchFunctionDrivetrainFrictionScreen(pros::screen_touch_status_s_t status){
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED){
        if (getPressed(status, 5, 5, 50, 50)){
            currentScene = HomeScreenScene;
        }
    }
}
