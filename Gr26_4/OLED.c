/*
 * OLED.c
 *
 * Created: 26.09.2024 12:54:14
 *  Author: torstepu
 */ 
#include "OLED.h"

void OLED_write_cmd(uint8_t adress){
	volatile char *ext_mem = (char*) XMEM_OLED_CMD;
	ext_mem[0] = adress;
}

void OLED_write_data(uint8_t adress){
	volatile char *ext_mem = (char*) XMEM_OLED_DATA;
	ext_mem[0] = adress;
}

void OLED_set_brightness(uint8_t level){
	OLED_write_cmd(0x81);
	OLED_write_cmd(level);
}

void OLED_reset(){
	for (uint8_t page = 0; page < 8; page++){
		OLED_write_cmd(0xB0|page); //Set page address
		OLED_write_cmd(0x00); //Set lower column address
		OLED_write_cmd(0x10); //Set higher column address
		for (uint8_t col = 0; col < 128; col++){
			OLED_write_data(0x00);
		}
	}
}


void OLED_init(){
	OLED_write_cmd(0xae); // display off
	OLED_write_cmd(0xa1); //segment remap
	OLED_write_cmd(0xda); //common pads hardware: alternative
	OLED_write_cmd(0x12);
	OLED_write_cmd(0xc8); //common output scan direction:com63~com0
	OLED_write_cmd(0xa8); //multiplex ration mode:63
	OLED_write_cmd(0x3f);
	OLED_write_cmd(0xd5); //display divide ratio/osc. freq. mode
	OLED_write_cmd(0x80);
	OLED_write_cmd(0x81); //contrast control
	OLED_write_cmd(0x50);
	OLED_write_cmd(0xd9); //set pre-charge period
	OLED_write_cmd(0x21);
	OLED_write_cmd(0x20); //Set Memory Addressing Mode
	OLED_write_cmd(0x02);
	OLED_write_cmd(0xdb); //VCOM deselect level mode
	OLED_write_cmd(0x30);
	OLED_write_cmd(0xad); //master configuration
	OLED_write_cmd(0x00);
	OLED_write_cmd(0xa4); //out follows RAM content
	OLED_write_cmd(0xa6); //set normal display
	OLED_write_cmd(0xaf); // display on
	OLED_write_cmd(0xa5); //Turn all pixels on
}