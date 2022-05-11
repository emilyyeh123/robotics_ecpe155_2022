/*
 * Trans_Reciever.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Uri
 */

#ifndef TRANS_RECIEVER_H_
#define TRANS_RECIEVER_H_

// packet structure
#define START_COMMAND 0xAA
#define END_COMMAND 0x55
#define TEST_CASE 0x04

// Movement Commands
#define MOVE_TOWARD_WP 0x05
#define NO_WP_IN_SIGHT 0x06
#define TASK_COMPLETE 0x07
#define moveForward 0x01
#define moveBackward 0x02
#define turnRight 0x03
#define turnLeft 0x04
#define moveToXY 0x05


// IR Commands
#define rightFrontIR 0x11
#define leftFrontIR 0x12
#define rightSideIR 0x13
#define leftSideIR 0x19


// avoid objects toggle
#define AVOID_OBJECT 0x14
#define objectEncounter 0x16


// Search next Way point
#define searchWaypoint 0x18

void initSerial();
void performAction();
void clearPacket(char *packet);
void sendPacket(char *packet_send);
void storeReceivedPacket(char *packet_rec);
void motorColorSearch();
void AutoForward();

//void jobComplete(char *packet_send);
//void objectDetected(char *packet_send);

#endif /* TRANS_RECIEVER_H_ */
