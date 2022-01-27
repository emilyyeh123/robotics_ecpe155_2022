/**
 * main.c
 */

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "gpio.h"
#include "sysctl.h"

static void delay( void ) {
  for( uint32_t i = 0; i < 250000; ++i );  // requires C99 mode
}

int main(void) {
    // Turn on run clock gate control for Port F.
    SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTF;

    // pin 1 - red
    // pin 2 - blue
    // pin 3 - green
    // Make RGB LEDs outputs and enable them.
    GPIO_PORTF[GPIO_DIR] |= GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_PORTF[GPIO_DEN] |= GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;

    while( 1 ) {
      // Turn the LED off, then delay
      GPIO_PORTF[GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3] &= ~(GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
      delay();

      // Turn it back on, then delay again
      GPIO_PORTF[GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3] |= (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
      delay();
    }
}
