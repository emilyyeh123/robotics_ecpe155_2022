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
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"



void initPWM(uint16_t period){
    // Enable PWM Module 0 (for M0PWM1 & M0PWM2) and wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){}

    // Enable the GPIOB peripheral (for PB7 & PB4) and wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}

    // Set up LEFT wheel (M0PWM1, PB7, Generator 0)
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7); // set PB7 as output
    GPIOPinConfigure(GPIO_PB7_M0PWM1);
    // Configure PWM generator for count down mode with immediate updates to the parameters.
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    // Set the period
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period);
    // set duty cycle
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, period);
    // Enable the output
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
    // Start timer in generator
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    // Set up RIGHT wheel (M0PWM2, PB4, Generator 1)
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4); // set PB7 as output
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    // Configure PWM generator for count down mode with immediate updates to the parameters.
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    // Set the period
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, period);
    // set duty cycle
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, period);
    // Enable the output
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    // Start timer in generator
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
}



void setPW(uint16_t PWL, uint16_t PWR){
    // modify duty cycle for M0PWM1 & M0PWM2
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, PWL); // left wheel
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, PWR); // right wheel
}
