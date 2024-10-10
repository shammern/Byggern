/*
 * MENU.h
 *
 * Created: 02.10.2024 12:47:17
 *  Author: sigvesm
 */ 

#include "OLED.h"
#include "ADC.h"
#include "GlobVariabel.h"
#include "GAME.h"

#ifndef MENU_H_
#define MENU_H_

typedef struct{
	uint8_t CURRENT_PAGE;
	uint8_t MENU_CHANGE;
} MENU;

typedef enum{
	GAME,
	CREDITS,
	SETTINGS,
	HIGHSCORE,
} MENU_CHOICE;

void menu_init();
void menu();
void update_parameters(MENU *menu_instance);
void game_menu();
void settings_menu();
void highscore_menu();



#endif /* MENU_H_ */