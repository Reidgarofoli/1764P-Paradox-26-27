#include "main.h"
#include "buttons.hpp"

void trackAngle(){
    int i = 0;
    int max = graph.size();
    while (true){
        if (i == max){
            return;
        }
        graph[i] = chassis.getPose().theta;
        power[i] = ldrive.get_voltage();
        i++;
        pros::delay(20);
    }
}
void trackMovement(){
    int i = 0;
    int max = graph.size();
    while (true){
        if (i == max){
            return;
        }
        graph[i] = chassis.getPose().y;
        power[i] = ldrive.get_voltage();
        i++;
        pros::delay(20);
    }
}

// void resetAngle(float normalAngleOfWall){
//     float d1 = bldist.get()/25.4; // left sensor
//     float d2 = brdist.get()/25.4; // right sensor

//     float dDist = 7.5; // dist between distance sensors inches

//     float d1Out = d1 - d2;
//     float d2Out = 0;

//     float angle = atanf(d1Out/dDist)*180/M_PI + normalAngleOfWall;

//     chassis.setPose(chassis.getPose().x, chassis.getPose().y, angle);
// }
void setX(pros::Distance *sensor, float offset, int invert){
    chassis.setPose(invert * (sensor->get()/25.4 + offset), chassis.getPose().y, chassis.getPose().theta);
}
void setY(pros::Distance *sensor, float offset, int invert){
    chassis.setPose(chassis.getPose().x, invert * (sensor->get()/25.4 + offset), chassis.getPose().theta);
}



void skillsAuton(){
switch(currentAuton){
    case 0:
        break;

    case 1:// big skills auto
        break;

    case 2://96 pt skills auto
        break;

    case 3: // end of skills parks and clears park
        break;

    case 4: // middle of skills clears park and scores whatever it picked up
        break;
    }
}





void runAuton(){
    if (currentSide == 'L'){
        switch (currentAuton){ // LEFT SIDE AUTONS
            case 0: // left 4
                chassis.setPose(0,0,0);
                clawState = true;//true means close claw, false means open claw
                claw.set_value(clawState);
                scoringState = ScoringState::DRIVING;
                chassis.moveToPoint(0, 10, 1500, {.forwards=true}, false);
                chassis.moveToPoint(0, -7, 1000, {.forwards=false}, false);
                chassis.moveToPoint(0, 10, 1500, {.forwards=true}, false);
                chassis.moveToPoint(0, -7, 1500, {.forwards=false}, false);
                chassis.moveToPoint(0, 15, 1500, {.forwards=true}, false);
                chassis.turnToHeading(270, 1000, {}, false);
                scoringState = ScoringState::LOWHIGH;
                pros::delay(500);
                chassis.moveToPoint(-15, 15, 1500, {.forwards=true}, false);
                clawState = false;
                claw.set_value(clawState);
                pros::delay(500);
                chassis.moveToPoint(0, 15, 1500, {.forwards=false}, false);
                scoringState = ScoringState::DRIVING;
                break;

            case 1: // split
                chassis.setPose(0,0,0);
                break;

            case 2:
                // AUTON 3 - left side 7 sit
                chassis.setPose(0,0,0);
                break;
            case 3:
                chassis.setPose(0,0,0);
                break;
            
            case 4:
                chassis.setPose(0,0,0);
                break;
            default:
                break;
        }


















    } else if (currentSide == 'R'){ // RIGHT SIDE AUTONS
        switch (currentAuton){
            case 0:
                chassis.setPose(0,0,90);
                break;
            case 1:
                chassis.setPose(0,0,0);
                break;
            case 2:
                chassis.setPose(0,0,90);
                break;
            case 3:
                chassis.setPose(0,0,0);
                break;
            case 4:
                chassis.setPose(0,0,0);
                break;
            default:
                break;
        }
 } else if (currentSide == 'S'){ // SKILLS AUTON
    skillsAuton();
    switch (currentAuton){
    case 0:
        chassis.setPose(0,0,0);
        break;

    case 1:
        chassis.setPose(0,0,90);
        break;
    
    case 2:
        chassis.setPose(0,0,0);
        break;
    
    }
        
    } else if (currentSide == 'T'){ // tune pid
        // pros::Task trackingAngleTask(trackAngle);
        // chassis.setPose(0,0,0);
        // chassis.turnToHeading(90, 100000, {}, false);
        // chassis.turnToHeading(180, 100000, {}, false);
        // chassis.turnToHeading(270, 100000, {}, false);
        // chassis.turnToHeading(0, 100000, {}, false);

        // pros::Task trackingMovementTask(trackMovement);
        // chassis.setPose(0,0,0);
        // chassis.moveToPoint(0, 36, 100000, {}, false);
        // chassis.moveToPoint(0, 0, 100000, {.forwards=false}, false);
        // chassis.moveToPoint(0, 36, 100000, {}, false);
        // chassis.moveToPoint(0, 0, 100000, {.forwards=false}, false);
    }
}