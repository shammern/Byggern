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
	
	if(x==1)
	{
		PORTC |= (0 << PC2) | (0 << PC3);
	}else if(x==2)
	{
		PORTC |= (1 << PC2) | (0 << PC3);
	}else if(x==3)
	{
		PORTC |= (0 << PC2) | (1 << PC3);
	}
}