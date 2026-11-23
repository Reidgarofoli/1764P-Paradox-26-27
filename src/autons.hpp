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

            case 1: // left side 3 pin from ground
                chassis.setPose(0,0,180);
                toggleState = true;
                toggle.set_value(toggleState);
                pros::delay(100);
                chassis.moveToPoint(0, 12, 2000, {.forwards=false, .maxSpeed=80, .minSpeed=70}, false); // back off of toggle (if it over rotates the toggle then lower max and min speed each by 5 or ten)
                toggleState = false;
                toggle.set_value(toggleState);
                intaking = 1; // intaking into the robot
                chassis.turnToPoint(0, 35, 2000, {.minSpeed=20, .earlyExitRange=5}, false);
                chassis.moveToPose(8, 38, 55, 2000, {.minSpeed=10, .earlyExitRange=1}, false); // grab cup from standing
                chassis.turnToHeading(45, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToHeading(65, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToPoint(-18, 14, 2000, {.forwards=false, .minSpeed=20, .earlyExitRange=3}, false); // grab cup from standing
                
                // raise cascade and back up to score first cup + pin
                intaking = 5;
                cascadeTarget = 1700;
                runintake = true;

                chassis.moveToPoint(-19, 12, 2000, {.forwards=false, .minSpeed=10, .earlyExitRange=1}, false);
                droppingmacro = true;
                dropping = true;
                ldrive.move(-40);
                rdrive.move(-40);
                pros::delay(300);
                dropping = false;
                pros::delay(600);

                // after dropping pin, intake next pin
                chassis.moveToPoint(-10, 12, 2000, {}, false);
                chassis.turnToHeading(-55, 2000, {}, false);
                intaking = 1;
                chassis.moveToPose(-30, 30, -45, 2000, {.lead=0.2}, false);
                chassis.moveToPoint(-10, 20, 2000, {.forwards=false}, false);
                chassis.turnToHeading(95, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToHeading(115, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToHeading(105, 1000, {}, false);
                chassis.moveToPose(-30, 30, 135, 2000, {.forwards=false}, false);


                break;

            case 2:
                // AUTON 3 - 4 pin from ground
                chassis.setPose(0,0,180);

                toggleState = true;
                toggle.set_value(toggleState);
                pros::delay(100);
                chassis.moveToPoint(0, 10, 2000, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false); // back off of toggle (if it over rotates the toggle then lower max and min speed each by 5 or ten)
                
                // stuff to make it put cascade all the way down while intaking
                intaking = 7;
                cascadeTarget = 0;
                runintake = true;
                toggleState = false;
                toggle.set_value(toggleState);

                chassis.turnToHeading(270, 2000, {.minSpeed=20, .earlyExitRange=5}, false);
                chassis.moveToPoint(13.5, 10, 2000, {.forwards=false, .minSpeed=20, .earlyExitRange=1}, false); // back up to alliance goal//max speed was 50
                ldrive.move(-40);
                rdrive.move(-40);
                
                intaking = 4; // outtake everything and drop the preload
                pros::delay(100);
                
                intaking = 3; // scoring macro, lifts up wrist while outtaking
                pros::delay(100);//works at 200
                intaking = 0;
                
                chassis.moveToPoint(10, 12, 2000, {.maxSpeed=80, .minSpeed=20, .earlyExitRange=3}, false); // back up to alliance goal//max speed was 50
                intaking = 1;
                chassis.moveToPoint(-14.5, 32, 2000, {.maxSpeed=80}, false);
                chassis.swingToHeading(305, DriveSide::LEFT, 2000, {.maxSpeed=80, .minSpeed=20, .earlyExitRange=5}, false);
                chassis.moveToPoint(-10, 30, 2000, {.forwards=false, .minSpeed=20, .earlyExitRange=2}, false);
                chassis.moveToPoint(1, 40, 2000, {.minSpeed=20, .earlyExitRange=2}, false);
                chassis.turnToHeading(65, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToHeading(35, 1000, {.minSpeed=30, .earlyExitRange=5}, false);

                // go back to alliance to drop the second pin
                chassis.moveToPoint(19, 19, 2000, {.forwards=false}, true);
                chassis.waitUntil(2);
                intaking = 5;
                cascadeTarget = 1500;
                runintake = true;
                chassis.waitUntilDone();
                droppingmacro = true;
                dropping = true;
                ldrive.move(-40);
                rdrive.move(-40);
                pros::delay(300);
                dropping = false;
                pros::delay(600);
                chassis.setPose(sin(chassis.getPose().theta * M_PI/180) * 7.5, cos(chassis.getPose().theta * M_PI/180) * 7.5, chassis.getPose().theta);

                chassis.moveToPoint(-11, 9, 1000, {.minSpeed=20, .earlyExitRange=3}, false);
                intaking = 1;
                chassis.moveToPoint(-43, 13, 1000, {}, false);
                chassis.swingToHeading(320, DriveSide::RIGHT, 2000, {}, false);
                chassis.moveToPoint(-33, 10, 1000, {.forwards=false}, false);
                chassis.turnToHeading(140, 1000, {}, false);
                
                // raise cascade w/ pin and grab cup
                intaking = 5;
                cascadeTarget = 1500;
                runintake = true;
                chassis.moveToPoint(-39, 19, 2000, {.forwards=false, .maxSpeed=60}, false);
                break;

            case 3://this is nuetral then allaince
                  chassis.setPose(0,0,180);//line up in middle
                toggleState = true;
                toggle.set_value(toggleState);
                pros::delay(100);
                chassis.moveToPoint(0, 12, 2000, {.forwards=false, .maxSpeed=80, .minSpeed=70}, false); // back off of toggle (if it over rotates the toggle then lower max and min speed each by 5 or ten)
                toggleState = false;
                toggle.set_value(toggleState);
                intaking = 1; // intaking into the robot
                chassis.turnToPoint(0, 35, 2000, {.minSpeed=20, .earlyExitRange=5}, false);
                chassis.moveToPose(8, 37, 55, 2000, {.minSpeed=10, .earlyExitRange=1}, false); // grab cup from standing//was y of 38
                chassis.turnToHeading(45, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToHeading(65, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToPoint(-18, 14, 2000, {.forwards=false, .minSpeed=20, .earlyExitRange=3}, false); // grab cup from standing
                pros::delay(500);
                // raise cascade and back up to score first cup + pin
                intaking = 5;
                cascadeTarget = 1700;
                runintake = true;
                
                chassis.moveToPoint(-19, 12, 2000, {.forwards=false, .minSpeed=10, .earlyExitRange=1}, false);
                droppingmacro = true;
                dropping = true;
                ldrive.move(-40);
                rdrive.move(-40);
                pros::delay(300);
                dropping = false;
                pros::delay(600);
                 cascadeTarget = 1700;

                intake.move(127);
                chassis.moveToPose(-2.7, 29.4,400,1000,{.minSpeed=100,}, false);
                intaking=1;
                chassis.turnToHeading(270,1000,{},false);
                chassis.moveToPose(-27,23,270,2000,{.maxSpeed=90},false);
                chassis.moveToPose(-18,15,300,1000,{.forwards=false},false);
                  intaking = 5;
                cascadeTarget = 800;
                runintake = true;//
            pros::delay (500);
                chassis.moveToPose(6.5,5.5,300,2000,{.forwards=false,.minSpeed=60,},false);
                pros::delay(500);
                intaking=5;
             droppingmacro = true;
                dropping = true;
                ldrive.move(-40);
                rdrive.move(-40);
                pros::delay(300);
                dropping = false;
                pros::delay(600);


                break;
            
            case 4://no mid line neut then allaince
  chassis.setPose(0,0,180);//line up in middle
                toggleState = true;
                toggle.set_value(toggleState);
                pros::delay(100);
                chassis.moveToPoint(0, 12, 2000, {.forwards=false, .maxSpeed=80, .minSpeed=70}, false); // back off of toggle (if it over rotates the toggle then lower max and min speed each by 5 or ten)
                toggleState = false;
                toggle.set_value(toggleState);
                intaking = 1; // intaking into the robot
                chassis.turnToPoint(0, 35, 2000, {.minSpeed=20, .earlyExitRange=5}, false);
                chassis.moveToPose(8, 37, 55, 2000, {.minSpeed=10, .earlyExitRange=1}, false); // grab cup from standing//was y of 38
                chassis.turnToHeading(45, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToHeading(65, 1000, {.minSpeed=30, .earlyExitRange=5}, false);
                chassis.turnToPoint(-18, 14, 2000, {.forwards=false, .minSpeed=20, .earlyExitRange=3}, false); // grab cup from standing
                
                // raise cascade and back up to score first cup + pin
                intaking = 5;
                cascadeTarget = 1700;
                runintake = true;

                chassis.moveToPoint(-19, 12, 2000, {.forwards=false, .minSpeed=10, .earlyExitRange=1}, false);
                droppingmacro = true;
                dropping = true;
                ldrive.move(-40);
                rdrive.move(-40);
                pros::delay(300);
                dropping = false;
                pros::delay(600);
                intaking= 4;
                chassis.moveToPose(0, 31,400,1000,{.minSpeed=100,}, false);
                intaking=1;
               
               
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