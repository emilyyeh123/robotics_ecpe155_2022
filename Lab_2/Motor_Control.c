/*
 * Motor_Control.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Uri
 */

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



void Motor_Forward(int period_right, int pulsewidth_right, int period_left, int pulsewidth_left)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
    // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz

    // Enable the PWM2, PWM3, GPIO B, and GPIO E peripheral modules
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Wait for the PWM module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM3))
    {
    }


    // Set PE4 & PE5 to be output. Theses will be used to signal forward motion on each wheel.
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5); // Set PE4 and PE5 to be output pins

    // Set PB0 & PB1 to be output. Theses will be used to signal backward motion on each wheel.
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1); // Set PB1 and PB2 to be output pins

    GPIOPinWrite(GPIO_PORTB_BASE, (GPIO_PIN_0 | GPIO_PIN_1), 0); // Ensure the pins for the backward direction are turned off.

    SysCtlDelay(1000);

    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4); // Turn on pin for forward motion in right wheel
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5); // Turn on pin for forward motion in left wheel


    // Set Pin J 1.7 to be a PWM2 Output Pin and set Pin J 1.2 to be a PWM3 Output Pin
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PB4_M0PWM2); // Configure pin 6 for PWM Module 2 Generator 0

    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PB5_M0PWM3); // Configure pin 6 for PWM Module 3 Generator 0



    // Configure the PWM2 and PWM3 generators (zero) for count down mode
    PWMGenConfigure(PWM2_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
    PWMGenConfigure(PWM3_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);



    // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
    // microseconds is recommended.
    //For a 40 MHz clock, this translates to 800 clock ticks.

    // Set the Period and Duty Cycle for the Right Wheel
    PWMGenPeriodSet(PWM2_BASE, PWM_GEN_0, period_right); //period of about 20 microseconds
    PWMPulseWidthSet(PWM2_BASE, PWM_OUT_2, pulsewidth_right);

    // Set the Period and Duty Cycle for the Left Wheel
    PWMGenPeriodSet(PWM3_BASE, PWM_GEN_0, period_left); //period of about 20 microseconds
    PWMPulseWidthSet(PWM3_BASE, PWM_OUT_3, pulsewidth_left);


    // Start the timers in both generator 0's.
    PWMGenEnable(PWM2_BASE, PWM_GEN_0);
    PWMGenEnable(PWM3_BASE, PWM_GEN_0);

    // Enable the outputs.
    PWMOutputState(PWM2_BASE, PWM_OUT_0_BIT, true);
    PWMOutputState(PWM3_BASE, PWM_OUT_0_BIT, true);

    // Repeat forever
    while (1)
    {

    }


}


void Motor_Backwards(int period_right, int pulsewidth_right, int period_left, int pulsewidth_left)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
    // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz

    // Enable the PWM2, PWM3, GPIO B, and GPIO E peripheral modules
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Wait for the PWM3 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM3))
    {
    }


    // Set PE4 & PE5 to be output. Theses will be used to signal forward motion on each wheel.
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5); // Set PE4 and PE5 to be output pins

    // Set PB0 & PB1 to be output. Theses will be used to signal backward motion on each wheel.
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1); // Set PB1 and PB2 to be output pins

    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_4 | GPIO_PIN_5), 0); // Ensure the pins for the forward direction are turned off.

    SysCtlDelay(1000);

    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_PIN_0); // Turn on pin for backward motion in right wheel
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1); // Turn on pin for backward motion in left wheel


    // Set Pin J 1.7 to be a PWM2 Output Pin and set Pin J 1.2 to be a PWM3 Output Pin
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PB4_M0PWM2); // Configure pin 6 for PWM Module 0 Generator 0

    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PB5_M0PWM3); // Configure pin 6 for PWM Module 0 Generator 0



    // Configure the PWM2 and PWM3 generators (zero) for count down mode
    PWMGenConfigure(PWM2_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
    PWMGenConfigure(PWM3_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);



    // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
    // microseconds is recommended.
    //For a 40 MHz clock, this translates to 800 clock ticks.

    // Set the Period and Duty Cycle for the Right Wheel
    PWMGenPeriodSet(PWM2_BASE, PWM_GEN_0, period_right); //period of about 20 microseconds
    PWMPulseWidthSet(PWM2_BASE, PWM_OUT_0, pulsewidth_right);

    // Set the Period and Duty Cycle for the Left Wheel
    PWMGenPeriodSet(PWM3_BASE, PWM_GEN_0, period_left); //period of about 20 microseconds
    PWMPulseWidthSet(PWM3_BASE, PWM_OUT_0, pulsewidth_left);


    // Start the timers in both generator 0's.
    PWMGenEnable(PWM2_BASE, PWM_GEN_0);
    PWMGenEnable(PWM3_BASE, PWM_GEN_0);

    // Enable the outputs.
    PWMOutputState(PWM2_BASE, PWM_OUT_0_BIT, true);
    PWMOutputState(PWM3_BASE, PWM_OUT_0_BIT, true);

    // Repeat forever
    while (1)
    {

    }


}








