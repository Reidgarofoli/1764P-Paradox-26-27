#pragma once
#include "../../drawing.hpp"


extern Scene GrapherScene;

extern Scene HomeScreenScene;

float scale = 1;
float centerValue = 36;

float scalePower = 1;
float centerValuePower = 0;

inline void drawGrapherScreen(){

    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);
    float horizontalScaleFactor = 480.0/(float)graph.size();
    
    pros::screen::set_pen(0x707070); // white pixel color
    pros::screen::draw_line(0, 120, 480, 120);
    pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 400+20, 65-50, "+");
    
    pros::screen::set_pen(0x707070); // white pixel color
    pros::screen::set_eraser(0x151570);
    for (int y = 60; y < 240; y+=40){
        pros::screen::draw_line(0, y, 480, y);
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, 0, y-5, "%0.2f", ((240 / 2.0f) - y) / scale);
    }
    pros::screen::set_pen(0xff5050);
    pros::screen::draw_line(0, 120, 480, 120);
    
    pros::screen::set_pen(0xffffff); // white pixel color
    for (int i = 1; i < graph.size(); i++){
        printf("x:%d y:%f\n", i, 120.0 - (graph[i] - centerValue) * scale);
        pros::screen::draw_line(horizontalScaleFactor*(i-1), 120.0 - (graph[i-1] - centerValue) * scale, horizontalScaleFactor*(i), 120.0 - (graph[i] - centerValue) * scale);
    }

    pros::screen::set_pen(0x0000ff); // blue pixel color
    for (int i = 1; i < power.size(); i++){
        printf("x:%d y:%f\n", i, 120.0 - (power[i] - centerValuePower) * scalePower);
        pros::screen::draw_line(horizontalScaleFactor*(i-1), 120.0 - (power[i-1] - centerValuePower) * scalePower, horizontalScaleFactor*(i), 120.0 - (power[i] - centerValuePower) * scalePower);
    }
    
    drawAsset(homeIcon_png, 5, 5, 50, 50);
    
    pros::screen::set_pen(0xffffff);
    drawRoundedRect(190, 10, 60, 40, 5);
    drawRoundedRect(260, 10, 60, 40, 5);
    drawRoundedRect(330, 10, 60, 40, 5);
    drawRoundedRect(400, 10, 60, 40, 5);
    pros::screen::set_pen(0x000000);
    pros::screen::set_eraser(0xffffff);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 190+20, 65-50, "-");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 260+20, 65-50, "+");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 330+20, 65-50, "-");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 400+20, 65-50, "+");
    
}

inline void touchFunctionGrapherScreen(pros::screen_touch_status_s_t status){
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED){
        if (getPressed(status, 5, 5, 50, 50)){
            currentScene = HomeScreenScene;
        } else if (getPressed(status, 330, 10, 60, 40)){
            scale/=2;
        } else if (getPressed(status, 400, 10, 60, 40)){
            scale*=2;
        } else if (getPressed(status, 190, 10, 60, 40)){
            scalePower/=2;
        } else if (getPressed(status, 260, 10, 60, 40)){
            scalePower*=2;
        }
    }
}
