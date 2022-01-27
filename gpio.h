/*
 * gpio.h
 *
 *  Created on: July 29, 2018
 *      Author: khughes
 *
 * GPIO register definitions.  See Chapter 10 of the TM4C1294 datasheet 
 * for complete information.
 */

#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>

// Peripheral base addresses.
#define GPIO_PORTF              ((volatile uint32_t *)0x4005D000)
#define GPIO_PORTN              ((volatile uint32_t *)0x40064000)

// Peripheral register offsets and special fields
enum {
#define   GPIO_PIN_1              (1 << 1) // pin 1
#define   GPIO_PIN_4              (1 << 4) // pin 4
#define   GPIO_ALLPINS            0b11111111 // pins 0 to 7
  GPIO_DIR  =   (0x400 >> 2),
  GPIO_DEN  =   (0x51c >> 2),
};

#endif // _GPIO_H
