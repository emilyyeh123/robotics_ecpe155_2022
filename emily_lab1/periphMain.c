/*
 * periphMain.c
 *
 *  Created on: Feb 2, 2022
 *      Author: emily
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

static void delay( void ) {
  for( uint32_t i = 0; i < 250000; ++i );  // requires C99 mode
}

int main(void) {
    // Enable GPIOF peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // pin 1 - red, pin 2 - blue, pin 3 - green
    // Make RGB LEDs outputs (set pins 1, 2, and 3 as output)
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3));

    while(1){
        // write some pins
        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3), (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3));
        delay();

        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3), 0);
        delay();
    }
}
