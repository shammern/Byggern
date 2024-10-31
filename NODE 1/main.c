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
#include "user_input.h"

CAN_MESSAGE receivedmsg;
JoyStick stick;
Slider slide;

void hardware_init(){
	xmem_init();
	
	USART_Init(MYUBRR);

	uart_setup_stdio();

	adc_init();
	
	OLED_init();
	
	CAN_init(MODE_NORMAL);
	
	pos_calibrate(&stick);
	
	printf("-------------------PROGRAM STARTV3-------------------\n");
}


ISR(INT2_vect){
	CAN_recieve(&receivedmsg);
	mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF | MCP_RX1IF, 0x00);	//Clears interupt flag
}


int main(void){	
	hardware_init();

	while(1){
		//send_user_input(&stick, &slide);
		printf("Sending message\n");
		get_user_input(&stick, &slide);
		send_user_input(&stick, &slide);
		
	}
}


