/*
 * Trans_Reciever.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Uri
 */

#ifndef TRANS_RECIEVER_H_
#define TRANS_RECIEVER_H_

void initSerial();
void recieveMess(char *packet_rec);
void jobComplete();
void objectDetected(char *packet_send);



#endif /* TRANS_RECIEVER_H_ */
