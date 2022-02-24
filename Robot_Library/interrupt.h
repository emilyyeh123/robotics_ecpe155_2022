/*
 * interrupt.h
 *
 *  Created on: Feb 23, 2022
 *      Author: Uri
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

// any source file that includes this will be able to use "count"
extern uint8_t count;

void initQEInterrupt();
void QEInterruptHandler();
uint8_t getCount();


#endif /* INTERRUPT_H_ */
