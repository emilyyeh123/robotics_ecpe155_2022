/*
 * gpio.h
 *
 *  Created on: July 29, 2018
 *      Author: khughes
 *
 * GPIO register definitions.  See Chapter 10 of the TM4C1294 datasheet 
 * for complete information.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

    // Peripheral base address
//#define _GPIO_PORT_F        ((volatile uint32_t *)0x4005D000) // Define GPIO_PORTF as a variable?
#define GPIO_PORT_F        ((volatile uint32_t *)0x40025000) // Define GPIO_PORTN as a variable? See changed address


// Peripheral register offsets and special fields
enum {
#define   GPIO_PIN_1              (1 << 1) // pin 1 - Red
#define   GPIO_PIN_2              (1 << 2) // pin 1 - Blue
#define   GPIO_PIN_3              (1 << 3) // pin 4 - Green
#define   GPIO_ALLPINS            0b11111111 // pins 0 to 7

  GPIO_DIR  =   (0x400 >> 2),
  GPIO_DEN  =   (0x51c >> 2),
};

#endif // _GPIO_H
