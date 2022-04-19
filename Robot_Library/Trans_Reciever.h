/*
 * Trans_Reciever.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Uri
 */

#ifndef TRANS_RECIEVER_H_
#define TRANS_RECIEVER_H_

// packet structure
#define startCommand 0xAA
#define endCommand 0x55

// Movement Commands
#define moveForward 0x01
#define moveBackward 0x02
#define turnRight 0x03
#define turnLeft 0x04
#define moveToXY 0x05

// IR Commands
#define rightIR 0x11
#define leftIR 0x12
#define backIR 0x13

void initSerial();
//void jobComplete(char *packet_send);
//void objectDetected(char *packet_send);
void performAction(char *packet_rec, char *packet_Send);
void initRecPacket(char *packet_rec);
void initSendPacket(char *packet_send);
void storeReceivedPacket(char *packet_rec);


#endif /* TRANS_RECIEVER_H_ */
