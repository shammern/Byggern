/*
 * ByggernGr26.c
 *
 * Created: 12.09.2024 09:16:29
 * Author : torstepu
 */ 
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <stdlib.h>
#include "UART.h"
#include "SRAM.h"
#include "XMEM.h"
//#include "NANDtest.h"
#include "ADC.h"
#include "OLED.h"
#include <string.h>
#include "MENU.h"
#include "GlobVariabel.h"
#include "SPI.h"
#include "CAN.h"
#include "MCP2515.h"


void hardware_init(){
	xmem_init();
	
	USART_Init(MYUBRR);

	uart_setup_stdio();

	adc_init();
	
	OLED_init();
	
	CAN_init(MODE_LOOPBACK);
	
	printf("-------------------PROGRAM STARTV3-------------------\n");
}

CAN_MESSAGE receivedmsg;

ISR(INT2_vect){
	CAN_recieve(&receivedmsg);
	mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF | MCP_RX1IF, 0x00);	
}


int main(void){	
	hardware_init();
	
	_delay_ms(1000);

	CAN_MESSAGE message;
	message.msg_ID = 0x0100;
	message.msg_length = 8;
	message.data[0] = 0xFF;
	message.data[1] = 0x22;
	message.data[2] = 0x33;
	message.data[3] = 0x44;
	message.data[4] = 0x55;
	message.data[5] = 0x66;
	message.data[6] = 0x77;
	message.data[7] = 0x88;
	
	printf("The sent data is: %x\n", message.data[0]); 
	
	CAN_transmit(&message);
	_delay_ms(1);
	//CAN_recieve(&receivedmsg);
	printf("The printed data is: %x\n", receivedmsg.data[0]); 
	
    while (1){
		//SPI_Test();
    }
}


