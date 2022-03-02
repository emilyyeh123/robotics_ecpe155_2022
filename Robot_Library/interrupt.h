/*
 * interrupt.h
 *
 *  Created on: Feb 23, 2022
 *      Author: Uri
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


// declare global vars
extern uint8_t revCountLeft;
extern uint8_t revCountRight;


void initQEInterrupt();
void QEInterruptHandler();
uint8_t getRevCountLeft();
uint8_t getRevCountRight();


#endif /* INTERRUPT_H_ */
