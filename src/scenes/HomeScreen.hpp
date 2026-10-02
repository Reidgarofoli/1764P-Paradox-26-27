#pragma once
#include "../drawing.hpp"

// forward declare other scene objects (avoid circular includes)
extern Scene AutonScreenScene;
extern Scene TourneyScreenScene;
extern Scene AppsScreenScene;

// forward declare other screens so we can switch to them


// pros::screen::set_pen(0x0d0d4a); // white pen
// drawRoundedRect(120, 60, 360, 180, 15);// big rounded rectangle that goes off the sides

inline void drawHomeScreen(){
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);


    // int logoWidth, logoHeight, logoChannels;
    // static unsigned char *logoImg = getImg("./assets/1764P-Logo.png", &logoWidth, &logoHeight, &logoChannels);
    // drawImg(logoImg, 20, 20, logoWidth, logoHeight, 440, 145);
    // drawImage("./assets/1764PLogo.png", 20, 20, 440, 145);
    drawAsset(Logo1764P_png, 20, 20, 440, 145);



    // buttons on bottom of screen
    pros::screen::set_pen(0x323232);
    // pros::screen::fill_rect(0, 190, 160, 240);
    // pros::screen::fill_rect(160, 190, 320, 240);
    // pros::screen::fill_rect(320, 190, 480, 240);
    pros::screen::draw_rect(0, 190, 160, 240);
    pros::screen::draw_rect(160, 190, 320, 240);
    pros::screen::draw_rect(320, 190, 480, 240);
    
    pros::screen::set_eraser(0x151570);
    pros::screen::set_pen(0xffffff);
    
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 30, 200, "MATCH");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 165, 200, "TOURNEY");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 360, 200, "APPS");

}

inline void touchFunctionHomeScreen(pros::screen_touch_status_s_t status){

    // check if settings button is pressed
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED){
        printf("Home Screen touched at (%d, %d)\n", status.x, status.y);
        if (getPressed(status, 0, 190, 160, 50)){
            currentScene = AutonScreenScene;
        } else if (getPressed(status, 160, 190, 160, 50)){
            currentScene = TourneyScreenScene;
        } else if (getPressed(status, 320, 190, 160, 50)){
            currentScene = AppsScreenScene;
        }
    }

}

extern Scene HomeScreenScene;