/*
 * Motor_Control.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_


void motorForward(uint16_t period_right, uint16_t pulsewidth_right, uint16_t period_left, uint16_t pulsewidth_left);
void motorBackward(uint16_t period_right, uint16_t pulsewidth_right, uint16_t period_left, uint16_t pulsewidth_left);
void motorStop();


#endif /* MOTOR_CONTROL_H_ */
