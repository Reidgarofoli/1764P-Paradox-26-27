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
                chassis.setPose(0,0,180);
                
                // stuff to make it put cascade all the way down while intaking
                intaking = 7;
                cascadeTarget = 0;
                runintake = true;

                toggleState = true;
                toggle.set_value(toggleState);
                pros::delay(100);
                chassis.moveToPoint(0, 12, 2000, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false); // back off of toggle (if it over rotates the toggle then lower max and min speed each by 5 or ten)
                chassis.turnToHeading(270, 2000, {}, false);
                chassis.moveToPoint(14, 12, 2000, {.forwards=false, .maxSpeed=100}, false); // back up to alliance goal//max speed was 50
                
                intaking = 4; // outtake everything and drop the preload
                pros::delay(100);

                intaking = 3; // scoring macro, lifts up wrist while outtaking
                pros::delay(100);//works at 200
                intaking = 0;

                chassis.moveToPoint(5, 12, 2000, {}, false);//added min speed at 70 but removed it cus missed
                chassis.turnToHeading(180, 1000, {}, false); // could add a distance reset here but it works fine rn
                toggleState = false;
                toggle.set_value(toggleState);
                chassis.moveToPose(18, 30, 225, 3000, {.forwards=false, .maxSpeed=100}, false); // backs up to the first standin pin
                
                // stuff to grab the standing pin
                intaking = 7; // lowering intake
                cascadeTarget = 0; // cascade lower all the way down
                runintake = true; // intake while lowering cascade
                pros::delay(400);

                //raise lift and move away
                intaking = 5;
                cascadeTarget = 1500;
                runintake = true;
                chassis.turnToPoint(20, 14, 2000, {.forwards=false}, false);
                chassis.moveToPoint(20, 14, 2000, {.forwards=false, .maxSpeed=100}, false);

                // stuff to lower down pin
                intaking = 7;
                cascadeTarget = 650;
                runintake = true;
                pros::delay(400);//works at 400

                // drop pin
                intaking = 3;
                cascadeTarget = 800;
                pros::delay(400);//works at 400

                chassis.moveToPoint(20, 38, 2000, {.forwards=true, .maxSpeed=100}, false);
                chassis.turnToHeading(-45, 2000, {}, false);
                chassis.moveToPoint(39, 14, 2500, {.forwards=false, .maxSpeed=100}, false);

//grab second pin
                intaking = 7; // lowering intake
                cascadeTarget = 0; // cascade lower all the way down
                runintake = true; // intake while lowering cascade
                pros::delay(400);//works at 400

                intaking = 5;
                cascadeTarget = 2400;
                runintake = true;
                chassis.moveToPoint(45,8, 2000, {.forwards=false, .maxSpeed=100}, false);
                chassis.turnToHeading(90, 2000, {}, false);
                chassis.moveToPoint(23, 14, 1200, {.forwards=false, .maxSpeed=120}, false);

                  intaking = 4;
                cascadeTarget = 1500;
                runintake = true;
                pros::delay(400);

                // drop pin
                intaking = 3;
                cascadeTarget = 0;
                pros::delay(300);


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
                chassis.setPose(0,0,0);
                break;
            case 1:
                chassis.setPose(0,0,0);
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