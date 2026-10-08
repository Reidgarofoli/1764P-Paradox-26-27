#pragma once
#include "../../drawing.hpp"


extern Scene DebugScreenScene;

extern Scene AutonScreenScene;
extern Scene TempsScreenScene;
extern Scene HomeScreenScene;

// float resetAngel(float normalAngleOfWall){
//     float d1 = bldist.get()/25.4; // left sensor
//     float d2 = brdist.get()/25.4; // right sensor

//     float dDist = 7.5; // dist between distance sensors inches

//     float d1Out = d1 - d2;
//     float d2Out = 0;

//     float angle = atanf(d1Out/dDist)*180/M_PI + normalAngleOfWall;

//     return angle;
// }

inline void drawDebugScreen(){
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);

    // title categories
    //outline buttons
    pros::screen::set_pen(0x323232);
    pros::screen::draw_rect(63, 7, 193, 52);
    pros::screen::draw_rect(200, 7, 335, 52);
    pros::screen::fill_rect(342, 7, 472, 52);

    pros::screen::set_eraser(0x151570);
    pros::screen::set_pen(0xffffff);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 75, 17, "AUTON");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 210, 17, "TEMPS");
    pros::screen::set_eraser(0x323232);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 355, 17, "DEBUG");
    
    drawAsset(homeIcon_png, 5, 5, 50, 50);



    pros::screen::set_eraser(0x0C284D);
    pros::screen::set_pen(0xFFFFFF);
    pros::screen::print(pros::E_TEXT_SMALL, 5, 40+24, "X pos:%.2f", chassis.getPose().x);
    pros::screen::print(pros::E_TEXT_SMALL, 5, 52+24, "Y pos:%.2f", chassis.getPose().y);
    pros::screen::print(pros::E_TEXT_SMALL, 5, 64+24, "Angle:%.2f", chassis.getPose().theta);

    pros::screen::print(pros::E_TEXT_SMALL, 5, 80+24, "rot:%d",   winch.get_position());


    // pros::screen::print(pros::E_TEXT_SMALL, 5, 80+24, "l:%.2f",   ldist.get()/25.4);
    // pros::screen::print(pros::E_TEXT_SMALL, 5, 94+24, "r:%.2f",   rdist.get()/25.4);
    // pros::screen::print(pros::E_TEXT_SMALL, 5, 108+24, "f:%.2f",  fdist.get()/25.4);
    // pros::screen::print(pros::E_TEXT_SMALL, 5, 122+24, "bl:%.2f", bldist.get()/25.4);
    // pros::screen::print(pros::E_TEXT_SMALL, 5, 136+24, "br:%.2f", brdist.get()/25.4);

    // pros::screen::print(pros::E_TEXT_SMALL, 25+50, 80+24, "%d",   ldist.get_confidence());
    // pros::screen::print(pros::E_TEXT_SMALL, 25+50, 94+24, "%d",   rdist.get_confidence());
    // pros::screen::print(pros::E_TEXT_SMALL, 25+50, 108+24, "%d",  fdist.get_confidence());
    // pros::screen::print(pros::E_TEXT_SMALL, 25+50, 122+24, "%d",  bldist.get_confidence());
    // pros::screen::print(pros::E_TEXT_SMALL, 25+50, 136+24, "%d",  brdist.get_confidence());

    // pros::screen::print(pros::E_TEXT_SMALL, 5+100, 80+24, "%d",  ldist.get_object_size());
    // pros::screen::print(pros::E_TEXT_SMALL, 5+100, 94+24, "%d",  rdist.get_object_size());
    // pros::screen::print(pros::E_TEXT_SMALL, 5+100, 108+24, "%d", fdist.get_object_size());
    // pros::screen::print(pros::E_TEXT_SMALL, 5+100, 122+24, "%d", bldist.get_object_size());
    // pros::screen::print(pros::E_TEXT_SMALL, 5+100, 136+24, "%d", brdist.get_object_size());

    // printing team + auton + side
    /*
    int currentAuton = 1; // will only be changed in buttons.cpp
    char currentTeam = 'R'; // 'R' or 'B'
    char currentSide = 'R'; // 'R' or 'L'
    */
    pros::screen::print(pros::E_TEXT_SMALL, 220, 40+24, "Team:%c", currentTeam);
    pros::screen::print(pros::E_TEXT_SMALL, 220, 52+24, "Side:%c", currentSide);
    pros::screen::print(pros::E_TEXT_SMALL, 220, 64+24, "Auton:%d", currentAuton);
    // pros::screen::print(pros::E_TEXT_SMALL, 220, 76+24, "resetAngle:%f", resetAngel(0));


    // Draw reset rotation sensor button
    pros::screen::set_pen(0x323232);
    pros::screen::draw_rect(342-30, 188, 472, 233);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 355-30, 198, "RESET ROT");

    updateScreen = true;
}

inline void touchFunctionDebugScreen(pros::screen_touch_status_s_t status){
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
        if (getPressed(status, 342-30, 188, 472, 233)){
            winch.set_position(0);
        }
    }
}