#pragma once
#include "display.hpp"



void getTouched(){
    pros::screen_touch_status_s_t status = pros::screen::touch_status();
    // pros::screen_touch_status_s_t status = raylibTouchStatus;
    
    updateScreen = true;

    currentScene.touchFunction(status);
    
}