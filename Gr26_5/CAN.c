/*
 * CAN.c
 *
 * Created: 10.10.2024 09:17:30
 *  Author: danienes
 */ 

#include "CAN.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void interrupt_init(){
	//disable interrupts
	cli();
	
	DDRE &= ~(1<<PE0);
	
	//Enable change of INT2 vector
	GICR = (1<<INT2);
	
	//interrupt on falling edge
	EMCUCR = ~(1<<ISC2);
	
	//Enable global interrupts, mulig denne er feil
	sei();
}

void isr_func(){
	
}

void CAN_init(uint8_t mode){
	//Init CAN in specified mode
	mcp2515_init();	
	mcp2515_set_mode(mode);
	
	//Recieve all msg/clear buffers
	mcp2515_write(MCP_RXB0CTRL, MCP_RXM1 | MCP_RXM0);
	
	//Enable interrupt flag for successful reception in buffer 0 and 1
	mcp2515_bit_modify(MCP_CANINTE, MCP_RX1IF | MCP_RX0IF, 0xFF);
	
	interrupt_init();
}


void CAN_transmit(CAN_MESSAGE *msg){
	
	mcp2515_write(MCP_TXB0SIDH, msg->msg_ID / 8);			//Sets 8 MSB in msgID
	mcp2515_write(MCP_TXB0SIDL, (msg->msg_ID % 8) << 5);	//Sets 3LSB in msgID
	mcp2515_write(MCP_TXB0DLC, msg->msg_length);		//Sets datalengt code bits
	for(int m = 0; m < msg->msg_length; m++){
		mcp2515_write(MCP_TXB0D0 + m, msg->data[m])
	}	
}

uint8_t CAN_recieve();