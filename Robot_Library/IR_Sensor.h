/*
 * IR_Sensor.h
 *
 *  Created on: Mar 15, 2022
 *      Author: Uri
 */

#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

extern uint32_t dist0, dist1, dist2;
>>>>>>> 41c426f9634eafe9fcbb183ed556f5527be9de11

void initIRSensor();
uint32_t getSensorData0();
uint32_t getSensorData1();
uint32_t getSensorData2();

#endif /* IR_SENSOR_H_ */
