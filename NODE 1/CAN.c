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
	
	//configures PE0 as interupt pin
	DDRE &= ~(1<<PE0);
	
	//Enable change of INT2 vector
	GICR = (1<<INT2);
	
	//interrupt on falling edge
	EMCUCR = ~(1<<ISC2);
	
	//Enable global interrupts
	sei();
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
	mcp2515_write(MCP_TXB0DLC, msg->msg_length);		//Sets datalength code bits
	for(int m = 0; m < msg->msg_length; m++){
		mcp2515_write(MCP_TXB0D0 + m, msg->data[m]);		//Puts data (one byte at a time) in send buffer
	}
	mcp2515_request_to_send();							//Sends data on send buffer
}

uint8_t CAN_recieve(CAN_MESSAGE *msg){
	if(mcp2515_read(MCP_CANINTF) & MCP_RX0IF){
		//Read from the buffers and set the id combined with the low and high bits
		uint8_t id_highbit = mcp2515_read(MCP_RXB0SIDH);
		uint8_t id_lowbit = mcp2515_read(MCP_RXB0SIDL);
		
		msg->msg_length = mcp2515_read(MCP_RXB0DLC);
		msg->msg_ID = (id_lowbit>>5) + (id_highbit<<3);
		for(int m = 0; m < msg->msg_length; m++){
			msg->data[m] = mcp2515_read(MCP_RXB0D0 + m);	
		}
	}
	else if(mcp2515_read(MCP_CANINTF) & MCP_RX1IF){
		//Read from the buffers and set the id combined with the low and high bits
		uint8_t id_highbit = mcp2515_read(MCP_RXB1SIDH);
		uint8_t id_lowbit = mcp2515_read(MCP_RXB1SIDL);
		
		msg->msg_length = mcp2515_read(MCP_RXB1DLC);
		msg->msg_ID = (id_lowbit>>5) + (id_highbit<<3);
		for(int m = 0; m < msg->msg_length; m++){
			msg->data[m] = mcp2515_read(MCP_RXB1D0 + m);	
		}
	}
	else{
		return 1;	
	}
	return 0;
}
