/*
 * interrupt.h
 *
 *  Created on: Feb 23, 2022
 *      Author: Uri
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


// declare global vars
extern uint16_t revCountLeft;
extern uint16_t revCountRight;

void initQEInterrupt();
void QEInterruptHandler();
uint16_t getRevCountLeft();
uint16_t getRevCountRight();
void clearCount();


#endif /* INTERRUPT_H_ */
