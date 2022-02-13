/*
 * PWM.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Uri
 *      Function designed to emit a
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



void PWM_Function(int period, int pulsewidth)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
    // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz

    // Enable the PWM0, GPIO B, and GPIO E peripheral modules
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Wait for the PWM0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
    {
    }

    // Set Pin J3.3 to be a PWM Output Pin
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6); // from LanchPad UM, J3 connector can control GPIO PB6 (pg10), From Tiva DS M0PWM0 is controlled by PB6 (pg1233).
    GPIOPinConfigure(GPIO_PB6_M0PWM0); // Configure pin 6 for PWM Module 0 Generator 0

    // Configure the PWM generator for count down mode
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
    //
    // Set the period. For a 50 KHz frequency, the period = 1/50,000, or 20
    // microseconds. For a 40 MHz clock, this translates to 800 clock ticks.
    // Use this value to set the period.
    //
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period); //period of about 20 microseconds
    //
    // Set the pulse width of PWM0 for a 25% duty cycle.
    //
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, pulsewidth);

    //
    // Start the timers in generator 0.
    //
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    // Enable the outputs.
    //
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);

    //SysCtlDelay(100000);
while (1)
{
}


}






