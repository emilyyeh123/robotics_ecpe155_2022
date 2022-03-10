/*
 * interrupt.h
 *
 *  Created on: Feb 23, 2022
 *      Author: Uri
 */

#ifndef QUADENCODER_H_
#define QUADENCODER_H_


// declare global vars
extern uint16_t revCountLeft;
extern uint16_t revCountRight;

void initQEInterrupt();
void QEInterruptHandler();
uint16_t getRevCountLeft();
uint16_t getRevCountRight();
void clearCount();


#endif /* QUADENCODER_H_ */
