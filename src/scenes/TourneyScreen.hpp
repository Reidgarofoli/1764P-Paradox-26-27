#include "../drawing.hpp"

inline void drawTourneyScreen(){
    pros::screen::set_pen(0x151570); // navy blue background
    pros::screen::fill_rect(0, 0, 480, 240);

    drawAsset(homeIcon_png, 5, 5, 50, 50);
}

inline void touchFunctionTourneyScreen(pros::screen_touch_status_s_t status){
    if (status.touch_status == pros::last_touch_e_t::E_TOUCH_PRESSED){
        if (getPressed(status, 5, 5, 50, 50)){
            currentScene = HomeScreenScene;
        }
    }
}

extern Scene TourneyScreenScene;