/*
 * sensor.h
 *
 *  Created on: Mar 2, 2022
 *      Author: emily
 */

#ifndef BUMPSENSOR_H_
#define BUMPSENSOR_H_


void initBumpSensorInterrupt();
void bumpSensorInterruptHandler();
bool getRightBumperTriggered();
bool getLeftBumperTriggered();
void clearBumpTriggers();
void bumpTriggered();


#endif /* BUMPSENSOR_H_ */
