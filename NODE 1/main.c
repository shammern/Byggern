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
#include "JoystickDriver.h"

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
	
// 	_delay_ms(1000);
// 
// 	CAN_MESSAGE message;
// 	message.msg_ID = 0x04;
// 	message.msg_length = 8;
// 	message.data[0] = 0x11;
// 	message.data[1] = 0x22;
// 	message.data[2] = 0x33;
// 	message.data[3] = 0x44;
// 	message.data[4] = 0x55;
// 	message.data[5] = 0x66;
// 	message.data[6] = 0x77;
// 	message.data[7] = 0x88;
	
	
	//printf("The sent data is: %x\n", message.data[0]); 
	
	//CAN_transmit(&message);
	//_delay_ms(1);
	
	
//     while (1){
// 		//CAN_transmit(&message);
// 		//printf("Sending data \n");
// 		//_delay_ms(1000);
// 		for(int i = 0; i < 8; i++){
// 			printf("The received data is: %x\n", receivedmsg.data[i]);
// 		}
// 		_delay_ms(2000);
//     }
// 	_delay_ms(1000);

	while(1){
		//send_user_input(&stick, &slide);
		printf("Sending message\n");
		get_user_input(&stick, &slide);
		send_user_input(&stick, &slide);
		_delay_ms(1000);
		
	}
}


