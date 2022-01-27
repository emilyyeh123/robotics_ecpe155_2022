/*
 * sysctl.h
 *
 *  Created on: Jan 26, 2022
 *      Author: emily
 */

#ifndef _SYSCTL_H
#define _SYSCTL_H

#include <stdint.h>

// Peripheral base addresses.
#define SYSCTL          (((volatile uint32_t *)0x400FE000))

// Peripheral register offsets and special fields.
enum {
   SYSCTL_RCGCGPIO =       (0x608 >> 2),
#define   SYSCTL_RCGCGPIO_PORTF (1 << 5)  // Port F
};

#endif // _SYSCTL_H
