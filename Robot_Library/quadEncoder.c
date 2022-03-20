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
#include "driverlib/pwm.h"

#include "Motor_Control.h"
#include "PWM.h"
#include "quadEncoder.h"

uint16_t revCountLeft;
uint16_t revCountRight;

void initQEInterrupt(){
    // initialize count variables
    clearCount();

    // Using PA3 and PA4 for QEA and QEB on left wheel
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}

    // Register the port-level interrupt handler. This handler is the first level interrupt handler for all the pin interrupts
    GPIOIntRegister(GPIO_PORTA_BASE, QEInterruptHandler);

    // Set Input pins to read encoder data
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, (GPIO_PIN_3 | GPIO_PIN_2));

    // Set pins for input signal from encoder
    // checking for both edges, so 64 ticks is one revolution
    GPIOIntTypeSet(GPIO_PORTA_BASE, (GPIO_PIN_3 | GPIO_PIN_2), GPIO_BOTH_EDGES);

    // Enable the Interrupts
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4);
}

void QEInterruptHandler(){
    // clear interrupt
    GPIOIntClear(GPIO_PORTA_BASE, (GPIO_PIN_3 | GPIO_PIN_4));

    // LEFT WHEEL - if QEA signal is high
    if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3) == GPIO_PIN_3){

        // increment left count variable
        revCountLeft++;
    }

    // RIGHT WHEEL - if QEA signal is high
    if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2) == GPIO_PIN_2){
        // increment Right count variable
        revCountRight++;
    }

/*
    // When the robot has traveled about 40 cm turn right
    if((revCountLeft >= 150) && (revCountRight >= 150)) {
        //motorLeftTurn90();
        motorStop();
        // Reset the counters
        revCountLeft = 0;
        revCountRight = 0;
    }
*/
}

uint16_t getRevCountLeft(){
    return revCountLeft;
}

uint16_t getRevCountRight(){
    return revCountRight;
}

void clearCount(){
    revCountLeft = 0;
    revCountRight = 0;
}
