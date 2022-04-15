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

#include "PWM.h"
#include "Motor_Control.h"
#include "quadEncoder.h"
#include "timer.h"

double angle;
double pose[] = {0, 0, 0};
double final_pose[] = {0, 0, 0};

// Initialize the motor
void initMotor(uint16_t period){
    initPWM(period);

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


// Move the robot forward at a user specified speed
void motorForward(uint16_t PWLeft, uint16_t PWRight){
    // set pulse width
    setPW(PWLeft, PWRight);

    // based on the HUB-ee control sheet,
    // Forward in1: Low, Forward in2: High
    // left wheel does the opposite (bc wheel placement mirrored)
    // - low pins: PE2 & PE4
    // - high pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_5 | GPIO_PIN_1), (GPIO_PIN_5 | GPIO_PIN_1));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);
}


// Move the robot backward at a user specified speed
void motorBackward(uint16_t PWLeft, uint16_t PWRight){
    // set pulse width
    setPW(PWLeft, PWRight);

    // based on the HUB-ee control sheet,
    // Forward in1: High, Forward in2: Low
    // left wheel does the opposite (bc wheel placement mirrored)
    // - high pins: PE2 & PE4
    // - low pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_4), (GPIO_PIN_2 | GPIO_PIN_4));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
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
        if((revCountRight >= 15) || (revCountLeft >= 15)){
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
        if((revCountRight >= 15) || (revCountLeft >= 15)){
            revCountRight = 0;
            revCountLeft = 0;

            return;
        }
    }

}

// Function to help keep the robot traveling in a straight line
void motorCorrection(){
    // Correct the robot trajectory if the left wheel moves faster than the right
    if((revCountRight >= (revCountLeft + 1)) && (revCountRight <= 200)) {
        // Stop moving the left wheel and allow the right wheel to catch up
        motorForward(200, 225);
        SysCtlDelay(500);
    }

    // Correct the robot trajectory if the left wheel moves faster than the right
    if((revCountLeft >= (revCountRight + 1)) && (revCountLeft <= 200)) {
        // Stop moving the left wheel and allow the right wheel to catch up
        motorForward(200, 225);
        SysCtlDelay(500);
    }
}

// Function to make the robot move in rectangle defined by a number of ticks
void motorRect(uint16_t x, uint16_t y){
    uint8_t count;

    count = 0;

    while(1){

        // I want to add a round function to convert distance to ticks ex: x = 20cm, x = 20*32 = tick numbers
        motorCorrection();
        SysCtlDelay(500);

        if(revCountLeft == x || revCountRight == x) {
            motorRightTurn90();
            motorForward(200,200);
            SysCtlDelay(500);
            revCountLeft = x + 1;
            revCountRight = x + 1;
            count++;
        }

        if(revCountLeft == x + y  || revCountRight == x + y){
            motorRightTurn90();
            motorForward(200,200);
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
    motorBackward(200,200);
    while((revCountRight <= 40) && (revCountLeft <= 40)){}
    clearCount();
}

// Turn the robot 45 degrees to the left
void motorLeftTurn45(){
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
void motorOrient(){
    revCountRight = 0;
    revCountLeft = 0;
    // The Period must be set to 800 for this function to work correctly
    // set pulse width
    setPW(200, 200);

    // Update the pose to this angle in Radians
    pose[2] = angle;

    // Convert the angle to a number of ticks for the encoder to use
    angle = lround(angle*30/3.14);

    // If the Angle is positive, robot rotates counter-clockwise
    if(angle == abs(angle))
    {
        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_5), (GPIO_PIN_2 | GPIO_PIN_5));
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);

        while(1){
            if((revCountRight >= angle) || (revCountLeft >= angle)){
                revCountRight = 0;
                revCountLeft = 0;
                return;
            }
        }
    }

    // If the Angle is negative, robot rotates clockwise
    if(angle < abs(angle))
    {
        angle = angle*(-1);
        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_4), (GPIO_PIN_1 | GPIO_PIN_4));
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);

        while(1){
            if((revCountRight >= angle) || (revCountLeft >= angle)){
                revCountRight = 0;
                revCountLeft = 0;

                return;
            }
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
        pose[0] = pose[0] * (-1);
    }

    else{
        return;
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
        if((revCountRight >= 30) || (revCountLeft >= 30)){
            revCountRight = 0;
            revCountLeft = 0;

            return;
        }
    }
}

void nav_xy(double x, double y){
    //assign final position
    final_pose[0] = x;
    final_pose[1] = y;

    // ensure the robot can orient to the goal position
    checkAngle();

    // determine the ticks needed to get to the goal position
    getAngle();

    // Rotate robot to face goal position
    motorOrient();

    motorForward(200, 200);
    initDrivetimer();
    initBumpSensorInterrupt();
    initIRSensor();

    if((pose[0] == final_pose[0]) && (pose[1] == final_pose[1])){
        motorStop();
        return;
    }
    getSensorData0();
    getSensorData1();
    getSensorData2();

}
