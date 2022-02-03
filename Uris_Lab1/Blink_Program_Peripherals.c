/*
 * Blink_Program_Peripherals.c
 *
 *  Created on: Feb 2, 2022
 *      Author: Uri







 * Blink Program
 * Uri Grunder
 * ECPE-155, Spring 2022
 * Toggle the on-board LED
 */

// Standard Inclusions
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"


// Use a procedure to delay long enough to see the LED change
static void delay( void ) {
  for( uint32_t i = 0; i < 500000; ++i );  // requires C99 mode
}


int main(void)
{
    // Enable the Peripheral Library for Pins in Port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Set output pins in Port F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    while (1) {

    // Set Pin 1 to 1
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1 ) ;
    delay();

    // Set Pin 1 to 0 and set Pin 2 to 1
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0) ;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2 ) ;
    delay();

    // Set Pin 2 to 0 and Pin 3 to 1
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0) ;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3 ) ;
    delay();


    }

}


