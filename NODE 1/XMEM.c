/*
 * CFile1.c
 *
 * Created: 12.09.2024 13:18:27
 *  Author: torstepu
 */ 

#include "XMEM.h"

void xmem_init(void)
{
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
}

void xmem_write(int8_t data, uint16_t addr)
{
	volatile char *ext_mem = (char*) XMEM_OLED_CMD;
	ext_mem[addr] = data;	
}

int8_t xmem_read(uint16_t addr)
{
	volatile char *ext_mem = (char*) XMEM_OLED_CMD;
	int8_t ret_value = ext_mem[addr];
	return ret_value;
}