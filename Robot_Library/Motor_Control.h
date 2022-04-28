/*
 * Motor_Control.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

extern bool startCount;
extern double pose[8];
extern double final_pose[8];
extern double angle;

void initMotor();
void motorForward(uint16_t vLeft,uint16_t vRight);
void motorBackward();
void travelTime(uint16_t distance);
void motorRightTurn90();
void motorLeftTurn90();
void motorRect(uint16_t x, uint16_t y);
void motorStop();
void motorBackAvoid();
void motorRightTurn45();
void motorLeftTurn45();
void motorAvoidLeftBump();
void motorAvoidRightBump();
void motorSelfOrient();
void motorUserOrient(uint8_t theta);
void motorLeftTurn180();
void getAngle();
void checkAngle();


#endif /* MOTOR_CONTROL_H_ */
