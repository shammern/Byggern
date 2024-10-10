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
	
	SPI_init();
	
	printf("-------------------PROGRAM STARTV3-------------------\n");
}



int main(void){	
	hardware_init();
	
	_delay_ms(1000);

	menu();
	
    while (1){
		//SPI_Test();
    }
}

