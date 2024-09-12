/*
 * ByggernGr26.c
 *
 * Created: 12.09.2024 09:16:29
 * Author : torstepu
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "UART.h"
#include "SRAM.h"
#include "XMEM.h"
#include "NANDtest.h"


int main(void)
{
	xmem_init();
	
    USART_Init(MYUBRR);

    uart_setup_stdio();

    printf("UART kommunikasjon er klar!\n");
	
	
	test_nand(2);
	
    while (1) 
    {
		
    }
}

