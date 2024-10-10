/*
 * OLED.h
 *
 * Created: 26.09.2024 12:54:02
 *  Author: torstepu
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include "XMEM.h"
#include <string.h>
#include <util/delay.h>


#ifndef OLED_H_
#define OLED_H_

void OLED_init();
void OLED_reset();
void OLED_home();
void OLED_goto_page(uint8_t page);
void OLED_goto_col(uint8_t col);
void OLED_clear_page(uint8_t page);
void OLED_pos(uint8_t page, uint8_t col);
void OLED_set_brightness(uint8_t level);

void OLED_write_cmd(uint8_t adress);
void OLED_write_data(uint8_t adress); //volatile
void OLED_print(char* charr);
void OLED_print_arrow(uint8_t page, uint8_t col);
void OLED_print_string(char* str);
void OLED_invert(uint8_t page, const char* str);
void OLED_gamescreen();
void OLED_settingscreen();
void OLED_highscorescreen();
void OLED_credits();



#endif /* OLED_H_ */