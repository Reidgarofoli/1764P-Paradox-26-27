#pragma once
#include "../../drawing.hpp"
#include <algorithm>


extern Scene AutonScreenScene;

extern Scene TempsScreenScene;
extern Scene DebugScreenScene;
extern Scene HomeScreenScene;
std::vector<std::string> leftAutonNames = {
    "4 wing",
    "split",
    "7 sit",
    "7 wing",
    "3-4+sit"
};
ScrollableList leftAutonList = {
    0,
    0
};
std::vector<std::string> rightAutonNames = {
    "awp",
    "4 wing",
    "split",
    "7 sit",
    "7 wing",
};
ScrollableList rightAutonList = {
    0,
    -1
};
std::vector<std::string> skillsAutonNames = {
    "1st bad one",
    "awp skills start",
    "u better not use"
};
ScrollableList skillsAutonList = {
    0,
    -1
};
inline void drawAutonScreen(){
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);

    // title categories
    //outline buttons
    pros::screen::set_pen(0x323232);
    pros::screen::fill_rect(63, 7, 193, 52);
    pros::screen::draw_rect(200, 7, 335, 52);
    pros::screen::draw_rect(342, 7, 472, 52);

    pros::screen::set_eraser(0x151570);
    pros::screen::set_pen(0xffffff);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 210, 17, "TEMPS");
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 355, 17, "DEBUG");
    pros::screen::set_eraser(0x323232);
    pros::screen::print(pros::text_format_e_t::E_TEXT_LARGE, 75, 17, "AUTON");

    drawAsset(homeIcon_png, 5, 5, 50, 50);



    pros::screen::set_eraser(0x151570);
    pros::screen::set_pen(0xffffff);
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 50, 65, "left");
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 190, 65, "right");
    pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM, 330, 65, "skills");

    // pros::screen::draw_rect(10, 100, 160, 230);
    // pros::screen::draw_rect(170, 100, 330, 230);
    // pros::screen::draw_rect(330, 100, 470, 230);
    drawScrollableList(leftAutonList, leftAutonNames, 10, 100, 150, 130, 30, pros::text_format_e_t::E_TEXT_MEDIUM, 0xffffff, 0x323232, 0x151570);
    drawScrollableList(rightAutonList, rightAutonNames, 165, 100, 150, 130, 30, pros::text_format_e_t::E_TEXT_MEDIUM, 0xffffff, 0x323232, 0x151570);
    drawScrollableList(skillsAutonList, skillsAutonNames, 320, 100, 150, 100, 30, pros::text_format_e_t::E_TEXT_MEDIUM, 0xffffff, 0x323232, 0x151570);

    pros::screen::set_pen(0xffffff);
    if (currentTeam == 'R') {
        pros::screen::set_pen(0xff0000);
    } else if (currentTeam == 'B'){
        pros::screen::set_pen(0x0000ff);
    }
    pros::screen::fill_rect(320, 200, 470, 230);
}
/*
ScrollableList& list,
const std::vector<std::string>& items,
int x, int y, int width, int height,
int itemHeight,
pros::text_format_e_t textFormat,
uint32_t textColor,
uint32_t selectedColor,
uint32_t backgroundColor
*/

/*
int currentAuton = 1; // will only be changed in buttons.cpp
char currentTeam = 'R'; // 'R' or 'B'
char currentSide = 'R'; // 'R' or 'L'
*/
inline void touchFunctionAutonScreen(pros::screen_touch_status_s_t status){
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
        if (getPressed(status, 320, 180, 150, 50)){
            if (currentTeam == 'R'){
                currentTeam = 'B';
            } else {
                currentTeam = 'R';
            }
        }
    }

    // Track which list had a selection change
    bool leftChanged = handleListScroll(leftAutonList, leftAutonNames, 10, 100, 150, 130, 30, status);
    bool rightChanged = handleListScroll(rightAutonList, rightAutonNames, 165, 100, 150, 130, 30, status);
    bool skillsChanged = handleListScroll(skillsAutonList, skillsAutonNames, 320, 100, 150, 130, 30, status);

    // Only one list can have a selected item at a time
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED) {
        if (leftChanged && leftAutonList.selectedIndex >= 0) {
            rightAutonList.selectedIndex = -1;
            skillsAutonList.selectedIndex = -1;
            currentAuton = leftAutonList.selectedIndex;
            currentSide = 'L';
        } else if (rightChanged && rightAutonList.selectedIndex >= 0) {
            leftAutonList.selectedIndex = -1;
            skillsAutonList.selectedIndex = -1;
            currentAuton = rightAutonList.selectedIndex;
            currentSide = 'R';
        } else if (skillsChanged && skillsAutonList.selectedIndex >= 0) {
            leftAutonList.selectedIndex = -1;
            rightAutonList.selectedIndex = -1;
            currentAuton = skillsAutonList.selectedIndex;
            currentSide = 'S';
            currentTeam = 'S';
        }
    }
}

