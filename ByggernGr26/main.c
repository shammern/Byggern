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
#include "NANDtest.h"
#include "ADC.h"


int main(void)
{
	xmem_init();
	
    USART_Init(MYUBRR);

    uart_setup_stdio();
	
	printf("-------------------PROGRAM START-------------------\n");

	adc_init();
	
    while (1) 
    {
		volatile uint8_t result = xmem_read(0x0400);
		printf("The value is: %u\n", result);
		_delay_ms(1000);
		
    }
}

