

/**
 * Blink Program
 * Uri Grunder
 * ECPE-155, Spring 2022
 * Toggle the on-board LED
 */

// Standard Inclusions
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

// TM4C hardware register and hand-crafted peripheral definitions.
#include "sysctl.h"
#include "gpio.h"

// Use a procedure to delay long enough to see the LED change
static void delay( void ) {
  for( uint32_t i = 0; i < 250000; ++i );  // requires C99 mode
}



int main(void)
{
    // Turn on run clock gate control for Port N.
    SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTF ;

    // Pin 1 is Red
    // Pin 2 is Blue
    // Pin 3 is Green
    // Make LED pins output(DIR) and enable them (DEN)
    GPIO_PORT_F[GPIO_DIR] |= (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3) ;
    GPIO_PORT_F[GPIO_DEN] |= (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3) ;

    while( 1 ) {
        // Turn All LEDs off and delay
       // GPIO_PORT_F[GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3] &= ~(GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3) ;
       // delay() ;

        //Turn on the Red LED
        GPIO_PORT_F[GPIO_PIN_1] |= GPIO_PIN_1 ;
        delay();

        // Turn off the Red LED and turn on the Blue LED, then delay
        GPIO_PORT_F[GPIO_PIN_1] &= ~GPIO_PIN_1 ;
        GPIO_PORT_F[GPIO_PIN_2] |= GPIO_PIN_2 ;
        delay();

        // Turn off the Blue LED and turn on the Green LED, then delay
        GPIO_PORT_F[GPIO_PIN_2] &= ~GPIO_PIN_2 ;
        GPIO_PORT_F[GPIO_PIN_3] |= GPIO_PIN_3 ;
        delay();

      }
}

