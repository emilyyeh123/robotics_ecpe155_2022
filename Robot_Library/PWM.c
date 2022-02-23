/*
 * PWM.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
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



void PWM_init(uint16_t period){
    // Enable the PWM0 module and wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){}

    // Enable the GPIOB module and wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}

    // set PB6 & PB7 as outputs
    GPIOPinTypePWM(GPIO_PORTB_BASE, (GPIO_PIN_6 | GPIO_PIN_7));
    GPIOPinConfigure(GPIO_PB7_M0PWM1); // left wheel
    GPIOPinConfigure(GPIO_PB6_M0PWM0); // right wheel

    // set pwm clock
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    // Configure the PWM generator for count down mode with immediate updates to the parameters.
    // set generator 0 for both wheels (PWM0 & PWM1)
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    // Set the period. For a 50 KHz frequency, the period = 1/50,000, or 20
    // microseconds. For a 20 MHz clock, this translates to 400 clock ticks.
    // Use this value to set the period.
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period);

    // set duty cycle for M0PWM0 & M0PWM1
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, period); // left wheel
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, period); // right wheel

    // Start the timer in generator 0
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    // Enable the outputs for M0PWM0 & M0PWM1
    PWMOutputState(PWM0_BASE, (PWM_OUT_1_BIT | PWM_OUT_0_BIT), true);
}



void PWM_setPW(uint16_t PWL, uint16_t PWR){
    // modify duty cycle for M0PWM0 & M0PWM1
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, PWL); // left wheel
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, PWR); // right wheel
}
