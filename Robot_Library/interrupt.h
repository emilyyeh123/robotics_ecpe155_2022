/*
 * interrupt.h
 *
 *  Created on: Feb 23, 2022
 *      Author: Uri
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


extern uint8_t revCount; // define global var

void initQEInterrupt();
void QEInterruptHandler();
uint8_t getRevCount();


#endif /* INTERRUPT_H_ */
