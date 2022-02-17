/*
 * Motor_Control.h
 *
 *  Created on: Feb 12, 2022
 *      Author: Uri
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_


void motorForward(int period_right, int pulsewidth_right, int period_left, int pulsewidth_left);

void motorBackward(int period_right, int pulsewidth_right, int period_left, int pulsewidth_left);

void motorStop(void);

#endif /* MOTOR_CONTROL_H_ */
