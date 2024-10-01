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



int main(void)
{
	xmem_init();
	
    USART_Init(MYUBRR);

    uart_setup_stdio();
	
	printf("-------------------PROGRAM STARTV3-------------------\n");

	adc_init();
	
	//JoyStick Stick;
	//Slider Slide;
	//pos_calibrate(&Stick);
	
	OLED_init();
	_delay_ms(1000);
	OLED_reset();
	OLED_write_cmd(0xa4);
	
	
	
    while (1) 
    {
 		//test_adc(&Stick, &Slide);
 		_delay_ms(100);
		 //joyStickClick();
		
		

    }
}

