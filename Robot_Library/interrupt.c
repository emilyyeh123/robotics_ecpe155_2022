/*
 * interrupt.c
 *
 *  Created on: Feb 22, 2022
 *      Author: Uri
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"

#include "interrupt.h"

uint8_t revCountLeft;
uint8_t revCountRight;

void initQEInterrupt(){
    // initialize count variables
    revCountLeft = 0;
    revCountRight = 0;

    // Using PA3 and PA4 for QEA and QEB on left wheel
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {}

    // Register the port-level interrupt handler. This handler is the first level interrupt handler for all the pin interrupts
    GPIOIntRegister(GPIO_PORTA_BASE, QEInterruptHandler);

    // Set Input pins to read encoder data
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, (GPIO_PIN_3 | GPIO_PIN_2));

    // Set pins for input signal from encoder
    // checking for both edges, so 64 ticks is one revolution
    GPIOIntTypeSet(GPIO_PORTA_BASE, (GPIO_PIN_3 | GPIO_PIN_2), GPIO_BOTH_EDGES);

    // Enable GPIOF for LED control
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}
    // Set the output pins that control the LED: PF1 - red, PF2 - blue, PF3 - green
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2);

    // Enable the Interrupts
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2);
}

void QEInterruptHandler(){
    // clear interrupt
    GPIOIntClear(GPIO_PORTA_BASE, (GPIO_PIN_3 | GPIO_PIN_4));

    // LEFT WHEEL - if QEA signal is high
    if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3) == GPIO_PIN_3){
        // turn on Red LED and increment left count var
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        revCountLeft++;
    }

    // RIGHT WHEEL - if QEA signal is high
    if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2) == GPIO_PIN_2){
        // turn on Blue LED and increment right count var
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        revCountRight++;
    }
}



uint8_t getRevCountLeft(){
    return revCountLeft;
}

uint8_t getRevCountRight(){
    return revCountRight;
}
