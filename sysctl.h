/*
 * sysctl.h
 *
 *  Created on: July 29, 2018
 *      Author: khughes
 *
 * System Control register definitions.  See Chapter 5 of the TM4C1294 
 * datasheet for complete information.
 */

#ifndef _SYSCTL_H
#define _SYSCTL_H

#include <stdint.h>

// Peripheral base addresses.
#define SYSCTL          (((volatile uint32_t *)0x400fe000))

// Peripheral register offsets and special fields.
enum {
   SYSCTL_RCGCGPIO =       (0x608 >> 2),
#define   SYSCTL_RCGCGPIO_PORTF (1 << 5)  // Port F
#define   SYSCTL_RCGCGPIO_PORTN (1 << 12)  // Port N
};

#endif // _SYSCTL_H
