/*
 * Motor_Control.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Uri
 *
 *      This file contains the functions for forward, backward, and stopping motions of the robot
 */


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "inc/tm4c123gh6pm.h"


void motorForward(int period_right, int pulsewidth_right, int period_left, int pulsewidth_left)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
       // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz

       // Enable the PWM0, GPIO B, and GPIO E peripheral modules
       SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

       // Wait for the PWM module to be ready.
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
       {
       }


       /*
        *
        * Right Wheel
        *
        */

       // Set PE4 & PE5 to be output. Theses will be used to signal motion on the right wheel.
       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5 | GPIO_PIN_4); // Set PE4 and PE5 to be output pins


       // Turn on the forward direction pins
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5); // high pin
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0); // low pin


       /*
        * Configuring the PWM Pins
        */

       GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
       GPIOPinConfigure(GPIO_PB4_M0PWM2); // Configure pin 4 on connector J1.7 for Motion Control Module 0 PWM 2 Generator 1



       // Configure the PWM2 for count down mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);



       // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
       // microseconds is recommended.
       //For a 40 MHz clock, this translates to 800 clock ticks.


       // Set the Period and Duty Cycle for the Left Wheel
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, period_right); // user defined period
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, pulsewidth_right); // User defines duty-cycle


       // Start the timers in both generator 0's.
       PWMGenEnable(PWM0_BASE, PWM_GEN_1);

       // Enable the outputs.
       PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);


       /*
        *
        * Left Wheel
        *
        */


       // Set output pins that will be used to signal  motion on the left wheel.
       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2); // Set PE1 and PE2 to be output pins


       // Turn on the forward direction pins
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1); // high pin
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); // Low pin


       /*
        * Configuring the PWM Pins
        */

       GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
       GPIOPinConfigure(GPIO_PB7_M0PWM1); // Configure pin 7 on connector J3.4 for Motion Control Module 0 PWM 2 Generator 1



       // Configure the PWM2 and PWM3 generators (zero) for count down mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);



       // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
       // microseconds is recommended.
       //For a 40 MHz clock, this translates to 800 clock ticks.


       // Set the Period and Duty Cycle for the Left Wheel
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period_left); // user defined period
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, pulsewidth_left); // User defines duty-cycle


       // Start the timers in both generator 0's.
       PWMGenEnable(PWM0_BASE, PWM_GEN_0);

       // Enable the outputs.
       PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
}










void motorBackward(int period_right, int pulsewidth_right, int period_left, int pulsewidth_left)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
    // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz

    // Enable the PWM0, GPIO B, and GPIO E peripheral modules
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Wait for the PWM module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
    {
    }


    /*
     *
     * Right Wheel
     *
     */

    // Set PE4 & PE5 to be output. Theses will be used to signal motion on the right wheel.
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5 | GPIO_PIN_4); // Set PE4 and PE5 to be output pins


    // Turn on the backward direction pins
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4); // high pin
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0); // low pin


    /*
     * Configuring the PWM Pins
     */

    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PB4_M0PWM2); // Configure pin 4 on connector J1.7 for Motion Control Module 0 PWM 2 Generator 1



    // Configure the PWM2 for count down mode
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);



    // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
    // microseconds is recommended.
    //For a 40 MHz clock, this translates to 800 clock ticks.


    // Set the Period and Duty Cycle for the Left Wheel
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, period_right); // user defined period
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, pulsewidth_right); // User defines duty-cycle


    // Start the timers in both generator 0's.
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);

    // Enable the outputs.
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);


    /*
     *
     * Left Wheel
     *
     */


    // Set output pins that will be used to signal motion on the left wheel.
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2); // Set PE1 and PE2 to be output pins


    // Turn on the forward direction pins
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2); // Turn on pin for forward motion in left wheel
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0); // Turn on pin 2 for forward motion in left wheel


    /*
     * Configuring the PWM Pins
     */

    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PB7_M0PWM1); // Configure pin 7 on connector J3.4 for Motion Control Module 0 PWM 2 Generator 1



    // Configure the PWM2 and PWM3 generators (zero) for count down mode
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);



    // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
    // microseconds is recommended.
    //For a 40 MHz clock, this translates to 800 clock ticks.


    // Set the Period and Duty Cycle for the Left Wheel
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period_left); // user defined period
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, pulsewidth_left); // User defines duty-cycle


    // Start the timers in both generator 0's.
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    // Enable the outputs.
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);

}












void motorStop(void)
{
SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
// the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz

// Enable the PWM0, GPIO B, and GPIO E peripheral modules
SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

// Wait for the PWM module to be ready.
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
{
}


/*
 *
 * Right Wheel
 *
 */

// Set PE4 & PE5 to be output. Theses will be used to signal motion on the right wheel.
GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5 | GPIO_PIN_4); // Set PE4 and PE5 to be output pins


// Turn on both controlling pins to stop motion
GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4); // high pin
GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5); // high pin


/*
 *
 * Left Wheel
 *
 */

// Set output pins that will be used to signal motion on the left wheel.
GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2); // Set PE1 and PE2 to be output pins


// Turn on tboth controlling pins to stop motion
GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2); // high pin
GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_2); // high pin

}
