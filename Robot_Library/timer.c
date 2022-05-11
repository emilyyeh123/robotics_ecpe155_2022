/*
 * timer.c
 *
 *  Created on: Apr 15, 2022
 *      Author: Uri
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#include "PWM.h"
#include "Motor_Control.h"
#include "quadEncoder.h"
#include "LED.h"
#include "bumpSensor.h"
#include "Trans_Reciever.h"
#include "timer.h"

int e_old;
int e_new;
int setL;
int setR;

// Timer to control pose update
void initDriveTimer(){

    uint32_t period;
    e_old = 0;
    integral_old = 0;
    derivative_old = 0;
    setL = 300;
    setR = 330;

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) { }

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    // Set the time for delay at 3 seconds
    period = (SysCtlClockGet() * 3);

    TimerLoadSet(TIMER0_BASE, TIMER_A, period);

    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);

    IntEnable(INT_TIMER0A);

    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    IntMasterEnable();

    // Enable the timer
    TimerEnable(TIMER0_BASE, TIMER_A);

}


void Timer0IntHandler(void){

    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    //declare sampling time and control variables
    int sampl_time = 3;
    int kp = 20;
    int ki = 10;
    int kd = 10;

    // Determine the distance traveled by the robot
    int distC = round((revCountRight + revCountLeft/64*18.85));

    // Assume the angle is the same and update the robot position
    pose[0] = pose[0] + distC*cos(pose[3]);
    pose[1] = pose[1] + distC*sin(pose[3]);

    // Determine the velocity of each wheel in inches per second
    int velL = round(revCountLeft/sampl_time*18.85/32);
    int velR = round(revCountRight/sampl_time*18.85/32);

    // determine error between wheel velocities and control terms
    int e_new = velR - velL;
    int proportional_term = kp * e_new;
    int integral_term = ki*sampl_time/2*(e_new - e_old) + integral_old;
    integral_old = integral_term;
    int derivative_term = kd*(e_new - e_old)/sampl_time + derivative_old;
    derivative_old = derivative_term;

    // Replace the old error value
    e_old = e_new;

    // calculate the wheel speed modifier
    int modifier = proportional_term + integral_term + derivative_term;

/*
    if(velR > 1){
        displayBlueLED();
        SysCtlDelay(5000000);
    }

    clearLED();

    if(velL > 1){
        displayRedLED();
        SysCtlDelay(5000000);
    }
    clearLED();




    // Adjust the speeds of the slower wheel
    if(velR > velL){
        setL = modifier + setL;
        motorForward(setL, setR);
        displayBlueLED();
        SysCtlDelay(5000000);
    }
*/

    clearLED();
    // Update the speed of the right wheel
    if(velR != velL){
        setR = modifier + setR;
        motorForward(300, setR);
        displayGreenLED();
        SysCtlDelay(5000000);
    }

    clearLED();

    // If a threshold limit is reached, reset the wheel speeds
    if((velL > 12) || (velR > 12)){
        setL = 300;
        setR = 330;
        motorForward(setL, setR);
        displayRedLED();
        SysCtlDelay(5000000);
    }

    clearLED();



}

void stopTimer(){
    TimerDisable(TIMER0_BASE, TIMER_A);
}

