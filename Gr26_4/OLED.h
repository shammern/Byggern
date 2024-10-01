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
//#include "Fonts.h"

#ifndef OLED_H_
#define OLED_H_

void OLED_init();
void OLED_reset();
void OLED_home();
//void OLED_goto_line(line);
//void OLED_clear_line(line);
//void OLED_pos(uint8_t row, uint8_t column);
void OLED_set_brightness(uint8_t level);

void OLED_write_cmd(uint8_t adress);
void OLED_write_data(uint8_t adress); //volatile
void OLED_print(char* charr);




#endif /* OLED_H_ */