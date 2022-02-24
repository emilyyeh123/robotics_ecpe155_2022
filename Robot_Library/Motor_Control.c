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


void motorForward(uint16_t period_right, uint16_t pulsewidth_right, uint16_t period_left, uint16_t pulsewidth_left)
{
    // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
    // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // Enable the PWM0, GPIO B, GPIO E, and GPIO A peripheral modules
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}

       // Wait for the PWM module to be ready.
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)){}


       /*
        *
        * Right Wheel
        *
        */

       /*
        * Configuring the PWM Pins
        */
       GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
       GPIOPinConfigure(GPIO_PB4_M0PWM2); // Configure pin 4 on connector J1.7 for Motion Control Module 0 PWM 2 Generator 1

       // Set PE4 & PE5 to be output. Theses will be used to signal motion on the right wheel.
       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5 | GPIO_PIN_4); // Set PE4 and PE5 to be output pins
       GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
       GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_6 | GPIO_PIN_7), (GPIO_PIN_6 | GPIO_PIN_7));


       // Turn on the forward direction pins that determine the motion of the robot. This setting is forward.
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5); // high pin
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0); // low pin

       // Configure the PWM for count down mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);



       // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
       // microseconds is recommended.
       //For a 40 MHz clock, this translates to 800 clock ticks.

       // Set the Period and Duty Cycle for the right Wheel
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, period_right); // user defined period
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, pulsewidth_right); // User defined duty-cycle

       // Enable the outputs
       PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);

       // Start the timer in generator 1
       PWMGenEnable(PWM0_BASE, PWM_GEN_1);


       /*
        *
        * Left Wheel
        *
        */

       // Configure the PWM Pin
       GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
       GPIOPinConfigure(GPIO_PB7_M0PWM1);

       // Set the output pins that determine the motion of the robot. This setting is forward.
       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2));
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);// high pin
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); // low pin

       // Configure the PWM for count down mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);


       // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
       // microseconds is recommended.
       //For a 40 MHz clock, this translates to 800 clock ticks.

       // Set the Period and Duty Cycle for the right Wheel
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period_left); // User defined period

       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, pulsewidth_left); // User defined Duty-Cycle

       // Enable the output. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM1!!!
       PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true); //

       // Start the timer in generator zero
       PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}

void motorBackward(uint16_t period_right, uint16_t pulsewidth_right, uint16_t period_left, uint16_t pulsewidth_left)
{
    // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
    // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

       // Enable the PWM0, GPIO B, GPIO E, and GPIO A peripheral modules
       SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){}
       SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)){}
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}


       /*
        *
        * Right Wheel
        *
        */

       /*
        * Configuring the PWM Pins
        */
       GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
       GPIOPinConfigure(GPIO_PB4_M0PWM2); // Configure pin 4 on connector J1.7 for Motion Control Module 0 PWM 2 Generator 1

       // Set PE4 & PE5 to be output. Theses will be used to signal motion on the right wheel.
       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5 | GPIO_PIN_4); // Set PE4 and PE5 to be output pins
       GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7); // Set PA6 and PA7 to be output pins


       // Turn on the forward direction pins that determine the motion of the robot. This setting is backward.
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4); // high pin
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0); // low pin
       GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_6 | GPIO_PIN_7), (GPIO_PIN_6 | GPIO_PIN_7)); // Standby Pins set to high

       // Configure the PWM for count down mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);



       // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
       // microseconds is recommended.
       //For a 40 MHz clock, this translates to 800 clock ticks.

       // Set the Period and Duty Cycle for the right Wheel
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, period_right); // user defined period
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, pulsewidth_right); // User defined duty-cycle. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM2!!!

       // Enable the outputs. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM2!!!
       PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);

       // Start the timer in generator 1
       PWMGenEnable(PWM0_BASE, PWM_GEN_1);


       /*
        *
        * Left Wheel
        *
        */

       // Configure the PWM Pin
       GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
       GPIOPinConfigure(GPIO_PB7_M0PWM1); // Configure pin 7 on connector J3.4 for Motion Control Module 0 PWM 1 Generator 0

       // Set the output pins that determine the motion of the robot. This setting is backward.
       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2));
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);// high pin
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0); // low pin

       // Configure the PWM for count down mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);


       // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
       // microseconds is recommended.
       //For a 40 MHz clock, this translates to 800 clock ticks.

       // Set the Period and Duty Cycle for the right Wheel
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period_left); // User defined period

       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, pulsewidth_left); // User defined Duty-Cycle. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM1!!!

       // Enable the output. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM1!!!
       PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true); //

       // Start the timer in generator zero
       PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}

void motorStop(void)
{
    // Enable the 16MHz crystal in the main oscillator. The precision clock runs at a natural 400MHz
    // the system automatically divides by 2 so we code another divide by 5 to get a total of 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

       // Enable the PWM0, GPIO B, and GPIO E peripheral modules
       SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
      // SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

       // Wait for the PWM module to be ready.
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)){}


       /*
        *
        * Right Wheel
        *
        */

       /*
        * Configuring the PWM Pins
        */
       GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
       GPIOPinConfigure(GPIO_PB4_M0PWM2); // Configure pin 4 on connector J1.7 for Motion Control Module 0 PWM 2 Generator 1

       // Set PE4 & PE5 to be output. Theses will be used to signal motion on the right wheel.
       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5 | GPIO_PIN_4); // Set PE4 and PE5 to be output pins


       // Turn on the forward direction pins. Turning both on will stop motion
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4); // high pin
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5); // high pin

       // Configure the PWM for count down mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);



       // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
       // microseconds is recommended.
       //For a 40 MHz clock, this translates to 800 clock ticks.

       // Set the Period and Duty Cycle for the right Wheel
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 1); // user defined period
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 1); // User defined duty-cycle. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM2!!!

       // Enable the outputs. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM2!!!
       PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);

       // Start the timer in generator 1
       PWMGenEnable(PWM0_BASE, PWM_GEN_1);


       /*
        *
        * Left Wheel
        *
        */

       // Configure the PWM Pin
       GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
       GPIOPinConfigure(GPIO_PB7_M0PWM1); // Configure pin 7 on connector J3.4 for Motion Control Module 0 PWM 1 Generator 0

       // Turn on the forward direction pins. Turning both on will stop motion
       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2));
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);// high pin
       GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1); // high pin

       // Configure the PWM for count down mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);


       // Set the period. A 50 KHz frequency, period = 1/50,000, or 20
       // microseconds is recommended.
       //For a 40 MHz clock, this translates to 800 clock ticks.

       // Set the Period and Duty Cycle for the right Wheel
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 1); // User defined period

       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1); // User defined Duty-Cycle. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM1!!!

       // Enable the output. ENSURE THE NUMBER IN PWM_OUT MATCHES THE NUMBER IN MOPWM1!!!
       PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true); //

       // Start the timer in generator zero
       PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}


