/*
 * PWM.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Uri
 *      Function designed to emit a PWM signal
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



void PWM_Function(int period, int pulsewidth)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
    // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz

    // Enable the PWM0 and GPIO B peripheral modules
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Wait for the PWM0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
    {

    }

    // Configure the pins for PWM signal
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PB4_M0PWM2); // Configure pin 7 at connector J1.7 for Motion Control Module 0 PWM 2 Generator 1

    // Configure the PWM generator for count down mode
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
    //
    // Set the period. For a 50 KHz frequency, the period = 1/50,000, or 20
    // microseconds. For a 40 MHz clock, this translates to 800 clock ticks.
    // Use this value to set the period.
    //
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, period); //period of about 20 microseconds
    //
    // Set the pulse width of PWM2. Ensure that PWM_OUT is the same number as M0PWM2!
    //
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, pulsewidth);

    // Enable the outputs. Ensure that PWM_OUT is the same number as M0PWM2!
    //
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);

    //
    // Start the timers in generator 1
    //
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);

}






