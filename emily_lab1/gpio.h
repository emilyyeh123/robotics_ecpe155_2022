/*
 * gpio.h
 *
 *  Created on: Jan 26, 2022
 *      Author: emily
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

// Peripheral base addresses.
#define GPIO_PORTF              ((volatile uint32_t *)0x4005D000)

// Peripheral register offsets and special fields
enum {
#define   GPIO_PIN_1              (1 << 1) // pin 1
#define   GPIO_PIN_2              (1 << 2) // pin 2
#define   GPIO_PIN_3              (1 << 3) // pin 3
  GPIO_DIR  =   (0x400 >> 2),
  GPIO_DEN  =   (0x51c >> 2),
};


#endif /* GPIO_H_ */
