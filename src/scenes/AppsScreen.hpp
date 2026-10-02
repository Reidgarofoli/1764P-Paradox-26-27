#pragma once
#include "../drawing.hpp"


extern Scene AppsScreenScene;

extern Scene DrivetrainFrictionScreenScene;
extern Scene PIDTunerScreenScene;
extern Scene HomeScreenScene;
extern Scene GrapherScene;

inline void drawAppsScreen(){
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);

    drawAsset(homeIcon_png, 5, 5, 50, 50);
    
    drawAsset(drivetrain_png, 5, 70, 150, 150);
    drawAsset(PID_png, 160, 70, 150, 150);
    drawAsset(Graph_png, 320, 70, 150, 150);
    
}

inline void touchFunctionAppsScreen(pros::screen_touch_status_s_t status){
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED){
        if (getPressed(status, 5, 70, 150, 150)){
            currentScene = DrivetrainFrictionScreenScene;
        } else if (getPressed(status, 160, 70, 150, 150)){
            currentScene = PIDTunerScreenScene;
        } else if (getPressed(status, 5, 5, 50, 50)){
            currentScene = HomeScreenScene;
        } else if (getPressed(status, 320, 70, 150, 150)){
            currentScene = GrapherScene;
        }
    }
}