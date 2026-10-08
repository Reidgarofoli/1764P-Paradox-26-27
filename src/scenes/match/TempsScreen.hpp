#pragma once
#include "../../drawing.hpp"


extern Scene TempsScreenScene;

extern Scene AutonScreenScene;
extern Scene DebugScreenScene;
extern Scene HomeScreenScene;

inline void drawTempsScreen(){
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);

    // title categories
    //outline buttons
    pros::screen::set_pen(0x323232);
    pros::screen::draw_rect(63, 7, 193, 52);
    pros::screen::fill_rect(200, 7, 335, 52);
    pros::screen::draw_rect(342, 7, 472, 52);

    pros::screen::set_eraser(0x151570);
    pros::screen::set_pen(0xffffff);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 75, 17, "AUTON");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 355, 17, "DEBUG");
    pros::screen::set_eraser(0x323232);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 210, 17, "TEMPS");
    
    drawAsset(homeIcon_png, 5, 5, 50, 50);


    pros::screen::set_pen(0xffffff);
    pros::screen::set_eraser(0x151570);
    
    std::vector<std::string> overheatedMotorNames = {"ldrive[2]", "intake[1]"};

    for (int i = 0; i < ldrive.get_temperature_all().size(); i++){
        if (ldrive.get_temperature(i) >= 50) pros::screen::set_pen(0xff0000);
        else if (ldrive.get_temperature(i) >= 50) pros::screen::set_pen(0xff7b00);
        else pros::screen::set_pen(0xffffff);
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 20, 80 + i*10, "ldrive[%d]: %f", i, ldrive.get_temperature(i));
    }
    
    for (int i = 0; i < rdrive.get_temperature_all().size(); i++){
        if (rdrive.get_temperature(i) >= 50) pros::screen::set_pen(0xff0000);
        else if (rdrive.get_temperature(i) >= 50) pros::screen::set_pen(0xff7b00);
        else pros::screen::set_pen(0xffffff);
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 20, 110 + i*10, "rdrive[%d]: %f", i, rdrive.get_temperature(i));
    }
   

    pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 20, 140 + 0*11, "winch 1: %f", cascade.get_temperature(0));
    pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 20, 140 + 1*11, "winch 2: %f", cascade.get_temperature(1));
    pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 20, 150 + 2*11, "arm 1: %f", arm.get_temperature(0));
    pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 20, 150 + 3*11, "arm 2: %f", arm.get_temperature(1));
    pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 20, 150 + 4*11, "wrist: %f", wrist.get_temperature());

    for (int i = 0; i < overheatedMotorNames.size(); i++){
        pros::screen::set_pen(0xff0000);
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 300, 90 + i*10, "%s", overheatedMotorNames[i].c_str());
    }
    
    pros::screen::set_pen(0xffffff);
    pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 20, 220, "battery: %d", 30);
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 300, 70, "Overheated:");


    updateScreen = true;
}

inline void touchFunctionTempsScreen(pros::screen_touch_status_s_t status){
    // check if home button is pressed
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED){
        if (getPressed(status, 5, 5, 50, 50)){
            currentScene = HomeScreenScene;
        }
        if (getPressed(status, 63, 7, 130, 45)){
            currentScene = AutonScreenScene;
        }
        if (getPressed(status, 200, 7, 135, 45)){
            currentScene = TempsScreenScene;
        }
        if (getPressed(status, 342, 7, 130, 45)){
            currentScene = DebugScreenScene;
        }
    }
}