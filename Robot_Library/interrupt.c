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



void interroopt(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}

    // Register the port-level interrupt handler. This handler is the first level interrupt handler for all the pin interrupts
    GPIOIntRegister(GPIO_PORTA_BASE, interroopt_handler);

    // Set Input pins to read encoder data
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, (GPIO_PIN_3 | GPIO_PIN_4));

    // Set pins for input signal from encoder
    GPIOIntTypeSet(GPIO_PORTA_BASE, (GPIO_PIN_3 | GPIO_PIN_4), GPIO_BOTH_EDGES);

    // Set the output pins that control the LED
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2);

    // Enable the Interrupts
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2);

    IntMasterEnable();
}


void interroopt_handler(void)
{
    // When one signal is high
    if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3))
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        }
    // When both signals are high
    else if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3) == GPIO_PIN_3 && GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4) == GPIO_PIN_4)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }

    // When both signals are low
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1 | GPIO_PIN_2), 0);
    }


}
