/*
 * OLED.c
 *
 * Created: 26.09.2024 12:54:14
 *  Author: torstepu
 */ 

#include "OLED.h"
#include "Fonts.h"


void OLED_write_cmd(uint8_t adress){
	volatile char *ext_mem = (char*) XMEM_OLED_CMD;
	ext_mem[0] = adress;
}

void OLED_write_data(uint8_t adress){
	volatile char *ext_mem = (char*) XMEM_OLED_DATA;
	ext_mem[0] = adress;
}

void OLED_set_brightness(uint8_t level){
	if (level >= 0 && level < 256){
		OLED_write_cmd(0x81);
		OLED_write_cmd(level);
	}	
}

void OLED_reset(){
	for(uint8_t page = 0; page < 8; page++){
		OLED_clear_page(page);
	}
}

void OLED_goto_page(uint8_t page){
	if (0 <= page && page <= 7){
		OLED_write_cmd(0xb0+page);
	}
}

void OLED_goto_col(uint8_t col){
	if (0 <= col && col <= 127){
		OLED_write_cmd(0x00 + (col & 0x0F)); //Lower col address
		OLED_write_cmd(0x10 + (col >> 4)); //Upper col address
	}
}

void OLED_pos(uint8_t page, uint8_t col){
	OLED_goto_page(page);
	OLED_goto_col(col);	
}

void OLED_print(char* charr){
	if(' ' <= *charr && *charr <= '~'){
		for(int i = 0; i < FONT_SIZE; i++){
			OLED_write_data(pgm_read_byte(&(font8[*charr-32][i])));
		}
	}		
}

void OLED_print_string(char* str){
	for(int i = 0; i < strlen(str); i++){
		OLED_print(&str[i]);
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
	OLED_reset(); //Turns all pixels off
	OLED_pos(3,35);
	OLED_print_string("WELCOME"); //Prints welcome message on the screen
	_delay_ms(2000);
	OLED_reset();
}

void OLED_print_arrow (uint8_t page, uint8_t col)
{
	OLED_pos(page, col);
	OLED_write_data(0b00011000);
	OLED_write_data(0b00011000);
	OLED_write_data(0b01111110);
	OLED_write_data(0b00111100);
	OLED_write_data(0b00011000);
}void OLED_clear_page(uint8_t page){	OLED_goto_page(page);	for (uint8_t col = 0; col < 128; col++){
		OLED_write_data(0x00);
	}	}void OLED_home(){	OLED_reset();	OLED_pos(0,PADDING);	OLED_print_string("PLAY GAME");			OLED_pos(1,PADDING);	OLED_print_string("HIGHSCORE");			OLED_pos(2,PADDING);	OLED_print_string("SETTINGS");				OLED_pos(3,PADDING);	OLED_print_string("CREDITS");}void OLED_gamescreen(){	OLED_reset();	OLED_pos(0,PADDING);	OLED_print_string("NEW GAME");		OLED_pos(1,PADDING);	OLED_print_string("PLACEHOLDER");		OLED_pos(2,PADDING);	OLED_print_string("PLACEHOLDER");		OLED_pos(3,PADDING);	OLED_print_string("EXIT");}

void OLED_settingscreen(){
	OLED_reset();
	OLED_pos(0,PADDING);	OLED_print_string("SET BRIGHTNESS");		OLED_pos(1,PADDING);	OLED_print_string("SET DIFFICULTY");		OLED_pos(2,PADDING);	OLED_print_string("PLACEHOLDER");		OLED_pos(3,PADDING);	OLED_print_string("EXIT");
}

void OLED_highscorescreen(){
	OLED_reset();
	OLED_pos(0,PADDING);	OLED_print_string("SEE HIGHSCORES");		OLED_pos(1,PADDING);	OLED_print_string("RESET HIGHSCORE");		OLED_pos(2,PADDING);	OLED_print_string("PLACEHOLDER");		OLED_pos(3,PADDING);	OLED_print_string("EXIT");
}

void OLED_credits(){
	OLED_reset();
	OLED_pos(0, PADDING);
	OLED_print_string("THANK YOU!");
	_delay_ms(1000);
	OLED_pos(1, PADDING);
	OLED_print_string("TORSTEIN");
	_delay_ms(1000);
	OLED_pos(2, PADDING);
	OLED_print_string("DANIEL");
	_delay_ms(1000);
	OLED_pos(3, PADDING);
	OLED_print_string("SIGVE aka");
	_delay_ms(3000);
	OLED_pos(4, PADDING);
	OLED_print_string("MOTO MOTO");
	_delay_ms(10000);
	
}



void OLED_invert(uint8_t page, const char* str){
	OLED_pos(page, 0);
	
	for(uint8_t i = 0; i < 128; i++){
		OLED_write_data(0xff);
	}
	OLED_pos(page, PADDING);
	
	for(int i = 0; i < strlen(str); i++){
		for(int j = 0; j < FONT_SIZE; j++){
			uint8_t original_data = pgm_read_byte(&(font8[str[i]-32][j]));
			uint8_t inverted_data = ~original_data;
			OLED_write_data(inverted_data);
	}
}
}
