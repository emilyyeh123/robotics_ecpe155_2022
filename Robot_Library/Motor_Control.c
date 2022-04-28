/*
 * Motor_Control.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
 */


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/pwm.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/systick.h"

#include "PWM.h"
#include "Motor_Control.h"
#include "quadEncoder.h"
#include "timer.h"
#include "bumpSensor.h"

bool startCount = false;
double angle;
double pose[8];
double final_pose[8];

// Initialize the motor
void initMotor(){
    initPWM(800);

    // Enable GPIOE peripheral (in1 & in2) and wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}
    // set wheel control outputs for PE1, PE2, PE4, PE5
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5));

    // Enable GPIOA peripheral (standby) and wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}
    // set standby outputs
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, (GPIO_PIN_6 | GPIO_PIN_7));
    // set standby to active high
    GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_6 | GPIO_PIN_7), (GPIO_PIN_6 | GPIO_PIN_7));

}


// Move the robot forward
void motorForward(uint16_t vLeft, uint16_t vRight){
    // set pulse width
    setPW(vLeft, vRight);

    // based on the HUB-ee control sheet,
    // Forward in1: Low, Forward in2: High
    // left wheel does the opposite (bc wheel placement mirrored)
    // - low pins: PE2 & PE4
    // - high pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_5 | GPIO_PIN_1), (GPIO_PIN_5 | GPIO_PIN_1));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);
}


// Move the robot backward
void motorBackward(){
    // set pulse width
    setPW(300, 311);

    // based on the HUB-ee control sheet,
    // Forward in1: High, Forward in2: Low
    // left wheel does the opposite (bc wheel placement mirrored)
    // - high pins: PE2 & PE4
    // - low pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_4), (GPIO_PIN_2 | GPIO_PIN_4));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
}



// allow motion for specified time
void travelTime(uint16_t distance){
    // Convert User distance to time
    int time = round(distance / 13.3) * 100000;
/*
    // Set a timer (default in milliseconds?)
    SysTickPeriodSet(time);
    SysTickEnable();

    while(1){
        if(SysTickValueGet() >= time){
            break;
        }
    }
*/
    SysCtlDelay(time);
    // When timer runs down, stop the robot
    motorStop();
}




// Function to turn the robot right approximately 90 degrees
void motorRightTurn90(){
    revCountRight = 0;
    revCountLeft = 0;
    // The Period must be set to 800 for this function to work correctly
    // set pulse width
    setPW(210, 200);

    // based on the HUB-ee control sheet,
    // Forward in1: High, Forward in2: Low
    // left wheel does the opposite (bc wheel placement mirrored)
    // - high pins: PE2 & PE4
    // - low pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_4), (GPIO_PIN_1 | GPIO_PIN_4));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);


    while(1){
        if((revCountRight >= 14) || (revCountLeft >= 14)){
            revCountRight = 0;
            revCountLeft = 0;

            return;
        }
    }


}

// Function to turn the robot left approximately 90 degrees
void motorLeftTurn90(){
    revCountRight = 0;
    revCountLeft = 0;
    // The Period must be set to 800 for this function to work correctly
    // set pulse width
    setPW(210, 200);

    // based on the HUB-ee control sheet,
    // Forward in1: High, Forward in2: Low
    // left wheel does the opposite (bc wheel placement mirrored)
    // - low pins: PE2 & PE4
    // - high pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_5), (GPIO_PIN_2 | GPIO_PIN_5));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);

    while(1){
        if((revCountRight >= 15) || (revCountLeft >= 15)){
            revCountRight = 0;
            revCountLeft = 0;

            return;
        }
    }

}


// Function to make the robot move in rectangle defined by a number of ticks
void motorRect(uint16_t x, uint16_t y){
    uint8_t count;

    count = 0;

    while(1){


        if(revCountLeft == x || revCountRight == x) {
            motorRightTurn90();
            motorForward(300, 311);
            SysCtlDelay(500);
            revCountLeft = x + 1;
            revCountRight = x + 1;
            count++;
        }

        if(revCountLeft == x + y  || revCountRight == x + y){
            motorRightTurn90();
            motorForward(300, 311);
            SysCtlDelay(500);
            revCountLeft = 0;
            revCountRight = 0;
            count++;
        }

        // Stop the program after 4 turns
        if(count >= 4){
            motorStop();
            SysCtlDelay(900000000);
        }


    }
}


// Stop the robot from moving.
void motorStop(){
    // stop/brake in1 & in2 High - set all 4 pins high
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5), (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5));
}




void motorBackAvoid()
{
    motorBackward();
    while((revCountRight <= 40) && (revCountLeft <= 40)){}
    clearCount();
}




// Turn the robot 45 degrees to the left
void motorLeftTurn45(){
    revCountRight = 0;
    revCountLeft = 0;
    // The Period must be set to 800 for this function to work correctly
    // set pulse width
    setPW(210, 200);

    // based on the HUB-ee control sheet,
    // Forward in1: High, Forward in2: Low
    // left wheel does the opposite (bc wheel placement mirrored)
    // - low pins: PE2 & PE4
    // - high pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_5), (GPIO_PIN_2 | GPIO_PIN_5));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);

    while(1){
        if((revCountRight >= 6) || (revCountLeft >= 6)){
            revCountRight = 0;
            revCountLeft = 0;

            return;
        }
    }
}





// Turn the robot 45 degrees to the right
void motorRightTurn45(){
    revCountRight = 0;
    revCountLeft = 0;
    // The Period must be set to 800 for this function to work correctly
    // set pulse width
    setPW(210, 200);

    // based on the HUB-ee control sheet,
    // Forward in1: High, Forward in2: Low
    // left wheel does the opposite (bc wheel placement mirrored)
    // - high pins: PE2 & PE4
    // - low pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_4), (GPIO_PIN_1 | GPIO_PIN_4));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);


    while(1){
        if((revCountRight >= 6) || (revCountLeft >= 6)){
            revCountRight = 0;
            revCountLeft = 0;

            return;
        }
    }
}





// When robot is bumped on the right, back up and turn left
void motorAvoidLeftBump(){
    clearCount();
    // back up
    motorBackAvoid();
    SysCtlDelay(50000);

    // turn left
    motorLeftTurn45();
    SysCtlDelay(500000);

    // Stop motion
    motorStop();
    SysCtlDelay(500000);
}





// When robot is bumped on the left, back up and turn right
void motorAvoidRightBump(){
    clearCount();
    //back up
    motorBackAvoid();
    SysCtlDelay(50000);

    // turn right
    motorRightTurn45();
    SysCtlDelay(500000);

    // stop motion
    motorStop();
    SysCtlDelay(500000);
}




// Takes an angle (within plus/mins 90 degrees) and turns robot to face it.
void motorSelfOrient(){
    revCountRight = 0;
    revCountLeft = 0;
    // The Period must be set to 800 for this function to work correctly
    // set pulse width
    setPW(200, 200);

    // Update the pose to this angle in Radians
    pose[2] = angle;

    // Convert the angle to a number of ticks for the encoder to use
    int ticks = lround(angle*28/3.14);

    // If the Angle is positive, robot rotates counter-clockwise
    if(ticks == abs(ticks))
    {
        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_5), (GPIO_PIN_2 | GPIO_PIN_5));
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);

        while(1){
            if((revCountRight >= ticks) || (revCountLeft >= ticks)){
                revCountRight = 0;
                revCountLeft = 0;
                return;
            }
        }
    }

    // If the Angle is negative, robot rotates clockwise
    if(ticks < abs(ticks))
    {
        ticks = ticks*(-1);
        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_4), (GPIO_PIN_1 | GPIO_PIN_4));
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);

        while(1){
            if((revCountRight >= ticks) || (revCountLeft >= ticks)){
                revCountRight = 0;
                revCountLeft = 0;

                return;
            }
        }
    }

}





// User defined angle to turn robot, +/- 90
void motorUserOrient(uint8_t theta){
    revCountRight = 0;
    revCountLeft = 0;
    // The Period must be set to 800 for this function to work correctly
    // set pulse width
    setPW(200, 200);

    //convert user given degrees to radians
    double angle = theta*3.14/180;

    // Convert the angle to a number of ticks for the encoder to use
    theta = round(angle/3.14)*28;

    // If the Angle is positive, robot rotates counter-clockwise
    if(theta == abs(theta))
    {
        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_5), (GPIO_PIN_2 | GPIO_PIN_5));
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);

        while(1){
            if((revCountRight >= theta) || (revCountLeft >= theta)){
                revCountRight = 0;
                revCountLeft = 0;
                return;
            }
        }
    }

    // If the Angle is negative, robot rotates clockwise
    if(theta < abs(theta))
    {
        theta = theta*(-1);
        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_4), (GPIO_PIN_1 | GPIO_PIN_4));
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);

        while(1){
            if((revCountRight >= theta) || (revCountLeft >= theta)){
                revCountRight = 0;
                revCountLeft = 0;

                return;
            }
        }
    }

}





// Function to turn the robot left approximately 180 degrees
void motorLeftTurn180(){
    revCountRight = 0;
    revCountLeft = 0;
    // The Period must be set to 800 for this function to work correctly
    // set pulse width
    setPW(200, 200);

    // based on the HUB-ee control sheet,
    // Forward in1: High, Forward in2: Low
    // left wheel does the opposite (bc wheel placement mirrored)
    // - low pins: PE2 & PE4
    // - high pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_5), (GPIO_PIN_2 | GPIO_PIN_5));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);

    while(1){
        if((revCountRight >= 28) || (revCountLeft >= 28)){
            revCountRight = 0;
            revCountLeft = 0;

            return;
        }
    }
}






// Determine what angle the robot should face to arrive at the goal pose (in radians)
void getAngle(){
    double x = final_pose[0] - pose[0];
    double y = final_pose[1] - pose[1];

    angle = atan(y/x);
}




// Move the robot 180 degrees if the goal is located behind the robot
void checkAngle(){
    if((final_pose[0] - pose[0]) < 0) {
        motorLeftTurn180();
        final_pose[0] = final_pose[0] * (-1);
    }

    else {
        return;
    }
}






// Navigate the robot to a point on a plane
void nav_xy(double x, double y){
    //assign final position
    final_pose[0] = x;
    final_pose[1] = y;

    initBumpSensorInterrupt();
    initIRSensor();

    // ensure the robot can orient to the goal position
    checkAngle();

    // determine the ticks needed to get to the goal position
    getAngle();

    // Rotate robot to face goal position
    motorSelfOrient();

    motorForward(300, 311);
    if(startCount == true){
        initDriveTimer();
    }

    if((pose[0] == final_pose[0]) && (pose[1] == final_pose[1])){
        motorStop();
        startCount == false;
        return;
    }
// Revisions needed to incorporate sensor data for object avoidence

}

