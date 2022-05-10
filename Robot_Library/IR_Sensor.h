/*
 * IR_Sensor.h
 *
 *  Created on: Mar 15, 2022
 *      Author: Uri
 */

#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

extern uint32_t dist0, dist1, dist2, dist3;

void initIRSensor();
uint32_t getSensorData0();
uint32_t getSensorData1();
uint32_t getSensorData2();
uint32_t getSensorData3();

#endif /* IR_SENSOR_H_ */
