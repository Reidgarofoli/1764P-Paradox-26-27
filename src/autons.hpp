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
                chassis.moveToPoint(0, 8, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 500, {.forwards=false, .minSpeed=60}, false);
                chassis.moveToPoint(0, 6, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 800, {.forwards=false, .minSpeed=60}, false);
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0, 17, 1000, {.forwards=true}, false);//score toggle our color
                chassis.turnToHeading(90, 1000, {}, true);
                scoringState = ScoringState::AUTON;
                chassis.moveToPose(20, 20, 90, 1500, {.forwards=true, .lead=0.1}, false);//drive into alliance goal
               chassis.setPose(20,20,90);
                pros::delay(100);
                scoringState = ScoringState::SCOREAUTON;
                pros::delay(800);
                clawState = true;
                claw.set_value(clawState);
                pros::delay(500);
                scoringState = ScoringState::AUTON;
                chassis.moveToPoint(0, 18, 1500, {.forwards=false}, false);//back up out of alliance goal
                scoringState = ScoringState::NORMAL;
                chassis.turnToHeading(45, 1000, {}, false);
                chassis.moveToPose(24.8, 41.8, 45, 2500, {.forwards=true, .lead=.7, .minSpeed=15, .earlyExitRange=1}, false);//go to pin/cup on quad line
                pros::delay(500);
                clawState = false;
                claw.set_value(clawState);
                pros::delay(300);
                scoringState = ScoringState::LOWHIGH;
                chassis.turnToPoint(25, 28, 1000, {}, false);
                chassis.moveToPoint(29, 26, 1500, {.forwards=true, .minSpeed=30}, false);
                scoringState = ScoringState::GOINGDOWN;//score it 
                pros::delay(1000);
                clawState = true;
                claw.set_value(clawState);
                pros::delay(500);
                chassis.moveToPoint(23, 38, 1500, {.forwards=false, .minSpeed=30}, false);//back up out of alliance goal
            //     chassis.turnToHeading(135, 1000, {}, false);
            //   chassis.moveToPose(49, 17,135, 2500, {.forwards=true, .lead=0.7, .minSpeed=15, .earlyExitRange=1}, false);//go to 2nd pin/cup on quad line
            //      pros::delay(500);
            //     clawState = false;
            //     claw.set_value(clawState);
            //     pros::delay(800);
            //     scoringState = ScoringState::HIGHHIGH;//up for scoring
            //     chassis.turnToHeading(270, 1000, {}, false);
            //     chassis.moveToPose(22, 17, 270, 1500, {.forwards=true, .minSpeed=30}, false);
            //     pros::delay(100);
            //     scoringState = ScoringState::LOWHIGH;//score it
            //     pros::delay(1500);
            //     clawState = true;
            //     claw.set_value(clawState);
            //     chassis.moveToPoint(45, 19, 1500, {.forwards=false, .minSpeed=30}, false);//back up out of alliance goal
             


                break;

            case 1: // split
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0, 8, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 500, {.forwards=false, .minSpeed=60}, false);
                chassis.moveToPoint(0, 6, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 800, {.forwards=false, .minSpeed=60}, false);
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0, 17, 1000, {.forwards=true}, false);//score toggle our color
                chassis.turnToHeading(90, 1000, {}, true);
                scoringState = ScoringState::AUTON;
                chassis.moveToPose(20, 20, 90, 1500, {.forwards=true, .lead=0.1}, false);//drive into alliance goal
               chassis.setPose(20,20,90);
                pros::delay(100);
                scoringState = ScoringState::SCOREAUTON;
                pros::delay(800);
                clawState = true;
                claw.set_value(clawState);
                pros::delay(500);
                scoringState = ScoringState::AUTON;
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
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0, 8, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 500, {.forwards=false, .minSpeed=60}, false);
                chassis.moveToPoint(0, 6, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 800, {.forwards=false, .minSpeed=60}, false);
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0, 17, 1000, {.forwards=true}, false);//score toggle our color
                chassis.turnToHeading(-90, 1000, {}, true);
                scoringState = ScoringState::AUTON;
                chassis.moveToPose(-20, 17,-90, 1500, {.forwards=true, .lead=0.1}, false);//drive into alliance goal
                pros::delay(100);
                scoringState = ScoringState::SCOREAUTON;
                pros::delay(800);
                clawState = true;
                claw.set_value(clawState);
                scoringState = ScoringState::AUTON;
                pros::delay(500);
                chassis.moveToPoint(0, 15, 1500, {.forwards=false}, false);//back up out of alliance goal
                scoringState = ScoringState::NORMAL;
                chassis.turnToHeading(-45, 1000, {}, false);
                chassis.moveToPose(-24.5, 38, -45, 2500, {.forwards=true, .lead=.7, .minSpeed=15, .earlyExitRange=1}, false);//go to pin/cup on quad line
                pros::delay(500);
                clawState = false;
                claw.set_value(clawState);
                pros::delay(300);
                scoringState = ScoringState::LOWHIGH;
                chassis.turnToPoint(-23, 25, 1000, {}, false);
                chassis.moveToPoint(-23, 20, 1500, {.forwards=true, .minSpeed=30}, false);
                scoringState = ScoringState::GOINGDOWN;//score it 
                pros::delay(1000);
                clawState = true;
                claw.set_value(clawState);
                pros::delay(500);
                chassis.moveToPoint(-23, 35, 1500, {.forwards=false, .minSpeed=30}, false);//back up out of alliance goal
            //     chassis.turnToHeading(-135, 1000, {}, false);
            //   chassis.moveToPose(-49, 17,-135, 2500, {.forwards=true, .lead=0.7, .minSpeed=15, .earlyExitRange=1}, false);//go to 2nd pin/cup on quad line
            //      pros::delay(500);
            //     clawState = false;
            //     claw.set_value(clawState);
            //     pros::delay(800);
            //     scoringState = ScoringState::HIGHHIGH;//up for scoring
            //     chassis.turnToHeading(-270, 1000, {}, false);
            //     chassis.moveToPose(-22, 17, -270, 1500, {.forwards=true, .minSpeed=30}, false);
            //     pros::delay(100);
            //     scoringState = ScoringState::LOWHIGH;//score it
            //     pros::delay(1500);
            //     clawState = true;
            //     claw.set_value(clawState);
            //     chassis.moveToPoint(-45, 19, 1500, {.forwards=false, .minSpeed=30}, false);//back up out of alliance goal
        
                break;
            case 1:
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0, 8, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 500, {.forwards=false, .minSpeed=60}, false);
                chassis.moveToPoint(0, 6, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 800, {.forwards=false, .minSpeed=60}, false);
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0, 17, 1000, {.forwards=true}, false);//score toggle our color
                chassis.turnToHeading(-90, 1000, {}, true);
                scoringState = ScoringState::AUTON;
                chassis.moveToPose(-20, 17,-90, 1500, {.forwards=true, .lead=0.1}, false);//drive into alliance goal
                pros::delay(100);
                scoringState = ScoringState::SCOREAUTON;
                pros::delay(800);
                clawState = true;
                claw.set_value(clawState);
                scoringState = ScoringState::AUTON;
                pros::delay(500);
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
                chassis.moveToPoint(0, 8, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 500, {.forwards=false, .minSpeed=60}, false);
                chassis.moveToPoint(0, 6, 1000, {.forwards=true, .minSpeed=60}, false);
                chassis.moveToPoint(0, -7, 800, {.forwards=false, .minSpeed=60}, false);
                chassis.setPose(0,0,0);
                chassis.moveToPoint(0, 17, 1000, {.forwards=true}, false);//score toggle our color
                chassis.turnToHeading(90, 1000, {}, true);
                scoringState = ScoringState::AUTON;
                chassis.moveToPose(20, 20, 90, 1500, {.forwards=true, .lead=0.1}, false);//drive into alliance goal
               chassis.setPose(20,20,90);
                pros::delay(100);
                scoringState = ScoringState::SCOREAUTON;
                pros::delay(800);
                clawState = true;
                claw.set_value(clawState);
                pros::delay(500);
                scoringState = ScoringState::AUTON;
                chassis.moveToPoint(0, 18, 1500, {.forwards=false}, false);//back up out of alliance goal
                scoringState = ScoringState::NORMAL;
                chassis.turnToHeading(45, 1000, {}, false);
                chassis.moveToPose(24.8, 42.8, 45, 2500, {.forwards=true, .lead=.7, .minSpeed=15, .earlyExitRange=1}, false);//go to pin/cup on quad line
                pros::delay(500);
                clawState = false;
                claw.set_value(clawState);
                pros::delay(300);
                scoringState = ScoringState::LOWHIGH;
                chassis.turnToPoint(25, 28, 1000, {}, false);
                chassis.moveToPoint(29, 26, 1500, {.forwards=true, .minSpeed=30}, false);
                scoringState = ScoringState::GOINGDOWN;//score it 
                pros::delay(1000);
                clawState = true;
                claw.set_value(clawState);
                pros::delay(500);
                chassis.moveToPoint(23, 38, 1500, {.forwards=false, .minSpeed=30}, false);//back up out of alliance goal
                chassis.moveToPoint(29, 26, 1500, {.forwards=false, .minSpeed=30}, false);
                chassis.turnToHeading(-45,1000,{},false);
                chassis.moveToPoint(0,55,3000,{.forwards=true},false);

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