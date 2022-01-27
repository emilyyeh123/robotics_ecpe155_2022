

/**
 * Blink Program
 * Uri Grunder
 * ECPE-155, Spring 2022, 1/26/2022
 * Toggle the on-board LED
 */

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

// TM4C hardware register and peripheral definitions.
#include "sysctl.h"
#include "gpio.h"

// Use a procedure to delay long enough to see the LED change
static void delay( void ) {
  for( uint32_t i = 0; i < 250000; ++i );  // requires C99 mode
}

int main(void)
{
	// Turn on run clock gate control for Port N.
    SYSCTL[SYSCTL_RCGCGPIO] |= GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 ;

    // Pin 1 is Red
    // Pin 2 is Blue
    // Pin 3 is Green
    // Make LED pins output(DIR) and enable them (DEN)
    GPIO_PORTF[GPIO_DIR] |= GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 ;
    GPIO_PORTF[GPIO_DEN] |= GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 ;

    while( 1 ) {
        // Turn All LEDs off and delay
        GPIO_PORTF[GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3] &=~ GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 ;
        delay() ;

        //Turn on the Red LED
        GPIO_PORTF[GPIO_PIN_1] |= GPIO_PIN_1 ;
        delay();

        // Turn off the Red LED and turn on the Blue LED, then delay
        GPIO_PORTF[GPIO_PIN_1] &= ~GPIO_PIN_1 ;
        GPIO_PORTF[GPIO_PIN_2] |= GPIO_PIN_2 ;
        delay();

        // Turn off the Blue LED and turn on the Green LED, then delay
        GPIO_PORTF[GPIO_PIN_2] &= ~GPIO_PIN_2 ;
        GPIO_PORTF[GPIO_PIN_3] |= GPIO_PIN_3 ;
        delay();

      }
}

/**
 * //
// Exercise 01: GPIO
//

// Definitions for datatypes used in labs.
#include <stdint.h>
#include <stdbool.h>

// TM4C hardware register and peripheral definitions.
#include "sysctl.h"
#include "gpio.h"

// Use a procedure to delay long enough to see the LED change
static void delay( void ) {
  for( uint32_t i = 0; i < 250000; ++i );  // requires C99 mode
}

// Questions:
//  1. Which GPIO port is LED D3 on?
//  2. What is the port's base address?
//  3. Which GPIO pin is LED D3 on?
//  4. Which SYSCTL_RCGCGPIO bit needs to be set for LED D3's GPIO port? 

// main loop
void main( void ) {
  // Turn on run clock gate control for Port N.
  SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTF;

  // Make LED D1 (PN1) an output and enable it.
  GPIO_PORTF[GPIO_DIR] |= GPIO_PIN_4;
  GPIO_PORTF[GPIO_DEN] |= GPIO_PIN_4;

  while( true ) {
    // Turn the LED off, then delay
    GPIO_PORTF[GPIO_PIN_4] = 0;
    delay();
    // Turn it back on, then delay again
    GPIO_PORTF[GPIO_PIN_4] = GPIO_ALLPINS;
    delay();
  }
}
 *
 */
