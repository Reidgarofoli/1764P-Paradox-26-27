#pragma once
#include "../../drawing.hpp"


extern Scene PIDTunerScreenScene;

extern Scene HomeScreenScene;

inline void drawPIDTunerScreen(){
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);

    drawAsset(homeIcon_png, 5, 5, 50, 50);

    pros::screen::set_pen(0xd0d0d0);
    drawRoundedRect(20, 200, 200, 40, 10);
    drawRoundedRect(260, 200, 200, 40, 10);
    pros::screen::set_pen(0x151570);
    pros::screen::set_eraser(0xd0d0d0);
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 30, 205, "Run Angular");
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 270, 205, "Run Lateral");
    
    pros::screen::set_pen(0xffffff);
    drawRoundedRect(20, 60, 60, 40, 5);
    drawRoundedRect(20, 150, 60, 40, 5);
    
    drawRoundedRect(90, 60, 60, 40, 5);
    drawRoundedRect(90, 150, 60, 40, 5);
    
    drawRoundedRect(160, 60, 60, 40, 5);
    drawRoundedRect(160, 150, 60, 40, 5);
    
    
    drawRoundedRect(260, 60, 60, 40, 5);
    drawRoundedRect(260, 150, 60, 40, 5);
    
    drawRoundedRect(330, 60, 60, 40, 5);
    drawRoundedRect(330, 150, 60, 40, 5);
    
    drawRoundedRect(400, 60, 60, 40, 5);
    drawRoundedRect(400, 150, 60, 40, 5);

    pros::screen::set_pen(0x000000);
    pros::screen::set_eraser(0xffffff);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 20+20, 60+5, "+");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 20+20, 150+5, "-");
    
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 90+20, 60+5, "+");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 90+20, 150+5, "-");

    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 160+20, 60+5, "+");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 160+20, 150+5, "-");

    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 260+20, 60+5, "+");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 260+20, 150+5, "-");

    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 330+20, 60+5, "+");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 330+20, 150+5, "-");

    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 400+20, 60+5, "+");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 400+20, 150+5, "-");
    
    pros::screen::set_pen(0xffffff);
    pros::screen::set_eraser(0x151570);
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 20, 120,  "P:%.1f  I:%.1f  D:%.1f", chassis.angularPID.kP, chassis.angularPID.kI, chassis.angularPID.kD);
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 260, 120, "P:%.1f  I:%.1f  D:%.1f", chassis.lateralPID.kP, chassis.lateralPID.kI, chassis.lateralPID.kD);
}

inline void touchFunctionPIDTunerScreen(pros::screen_touch_status_s_t status){
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED){
        if (getPressed(status, 5, 5, 50, 50)){
            currentScene = HomeScreenScene;
        }

        // if (getPressed(status, 20, 60, 60, 40)){
        //     chassis.angularPID.kP += 0.1;
        // }
        // if (getPressed(status, 20, 150, 60, 40)){
        //     chassis.angularPID.kP -= 0.1;
        // }
        // if (getPressed(status, 90, 60, 60, 40)){
        //     chassis.angularPID.kI += 0.1;
        // }
        // if (getPressed(status, 90, 150, 60, 40)){
        //     chassis.angularPID.kI -= 0.1;
        // }
        // if (getPressed(status, 160, 60, 60, 40)){
        //     chassis.angularPID.kD += 0.5;
        // }
        // if (getPressed(status, 160, 150, 60, 40)){
        //     chassis.angularPID.kD -= 0.5;
        // }
        
        // if (getPressed(status, 260, 60, 60, 40)){
        //     chassis.lateralPID.kP += 0.1;
        // }
        // if (getPressed(status, 260, 150, 60, 40)){
        //     chassis.lateralPID.kP -= 0.1;
        // }
        // if (getPressed(status, 330, 60, 60, 40)){
        //     chassis.lateralPID.kI += 0.1;
        // }
        // if (getPressed(status,330, 150, 60, 40)){
        //     chassis.lateralPID.kI -= 0.1;
        // }
        // if (getPressed(status, 400, 60, 60, 40)){
        //     chassis.lateralPID.kD += 0.5;
        // }
        // if (getPressed(status, 400, 150, 60, 40)){
        //     chassis.lateralPID.kD -= 0.5;
        // }
    }
}
