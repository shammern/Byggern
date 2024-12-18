/*
 * CFile1.c
 *
 * Created: 12.09.2024 17:08:52
 *  Author: torstepu
 */ 

#include "NANDtest.h"

void test_nand(int x)
{
	
	DDRC |= (1 << PC3) | (1 << PC2);

		
	if (x == 1) // OLED
	{
		volatile char *adress = (char *) 0x1000;
		uint16_t i = 0;
		uint8_t retreived_value = adress[i];

	}
	else if (x == 2) // ADC
	{
		volatile char *adress = (char *) 0x1400;
		uint16_t i = 0;
		uint8_t retreived_value = adress[i];

	}
	else if (x == 3) // SRAM
	{
		volatile char *adress = (char *) 0x1800;
		uint16_t i = 0;
		uint8_t retreived_value = adress[i];

	}

}

