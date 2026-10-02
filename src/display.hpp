#pragma once

#include "drawing.hpp"


extern Scene HomeScreenScene;


void updateScreenTask(){
    currentScene = HomeScreenScene;
    while (true){
        if (updateScreen){
            updateScreen = false;
            currentScene.drawFunction();
        }

        pros::delay(updateDelay);
    }
}