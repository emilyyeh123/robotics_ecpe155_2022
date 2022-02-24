/*
 * Motor_Control.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
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

#include "PWM.h"



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



void motorStop(){
    // stop/brake in1 & in2 High - set all 4 pins high
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5), (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5));
}
