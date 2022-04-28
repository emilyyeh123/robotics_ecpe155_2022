/*
 * timer.h
 *
 *  Created on: Apr 15, 2022
 *      Author: Uri
 */

#ifndef TIMER_H_
#define TIMER_H_

void initDriveTimer();
void Timer0IntHandler(void);

int e_old;
int e_new;
int integral_old;
int derivative_old;
int setL;
int setR;

#endif /* TIMER_H_ */
