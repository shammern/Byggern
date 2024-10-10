/*
 * CAN.h
 *
 * Created: 10.10.2024 09:17:40
 *  Author: danienes
 */ 

#include "MCP2515.h"


#ifndef CAN_H_
#define CAN_H_


void interrupt_init();
void isr_func();
void CAN_transmit(CAN_MESSAGE* message);
uint8_t CAN_recieve(CAN_MESSAGE* message);
void CAN_init(uint8_t mode);

typedef struct{
	uint16_t msg_ID;
	uint8_t msg_length;
	uint8_t data[8];
} CAN_MESSAGE;


#endif /* CAN_H_ */