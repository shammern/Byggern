/*
 * MENU.c
 *
 * Created: 02.10.2024 12:47:35
 *  Author: sigvesm
 */ 

#include "MENU.h"

MENU MAIN_MENU;
MENU GAME_MENU;
MENU SETTINGS_MENU;
MENU HIGHSCORE_MENU;

JoyStick JOYSTICK;
Joystick_direction JOYSTICK_DIR = NEUTRAL;
Slider SLIDER;

//Maps for menu choices: 
const char* main_menu_map[] = {
	"PLAY GAME",    // key = 0
	"HIGHSCORE",    // key = 1
	"SETTINGS",     // key = 2
	"CREDITS"       // key = 3
};

const char* game_menu_map[] = {
	"NEW GAME",    // key = 0
	"PLACEHOLDER",    // key = 1
	"PLACEHOLDER",     // key = 2
	"EXIT"       // key = 3
};

const char* settings_menu_map[] = {
	"SET BRIGHTNESS",    // key = 0
	"SET DIFFICULTY",    // key = 1
	"PLACEHOLDER",     // key = 2
	"EXIT"       // key = 3
};

const char* highscore_menu_map[] = {
	"SEE HIGHSCORE",    // key = 0
	"RESET HIGHSCORE",    // key = 1
	"PLACEHOLDER",     // key = 2
	"EXIT"       // key = 3
};



void menu_init(){
	OLED_reset();
	OLED_home();
	OLED_invert(MAIN_MENU.CURRENT_PAGE, main_menu_map[MAIN_MENU.CURRENT_PAGE]);
	pos_calibrate(&JOYSTICK);
}

void update_parameters(MENU *menu_instance){
	
	adc_read(&JOYSTICK, &SLIDER);
	joyStickPos(&JOYSTICK);
	JOYSTICK_DIR = joyStickDir(&JOYSTICK);
	
	if(JOYSTICK_DIR != NEUTRAL){
		if(JOYSTICK_DIR == DOWN){
			if(menu_instance->CURRENT_PAGE == 3){
				menu_instance->CURRENT_PAGE = 0;
				menu_instance->MENU_CHANGE = 1;
			}
			else{
				menu_instance->CURRENT_PAGE++;
				menu_instance->MENU_CHANGE = 1;
			}
			
		}else if(JOYSTICK_DIR == UP){
			if(menu_instance->CURRENT_PAGE == 0){
				menu_instance->CURRENT_PAGE = 3;
				menu_instance->MENU_CHANGE = 1;
			}
			else{
				menu_instance->CURRENT_PAGE--;
				menu_instance->MENU_CHANGE = 1;
			}
		}
	}
	
	while (JOYSTICK_DIR != NEUTRAL){
		adc_read(&JOYSTICK, &SLIDER);
		joyStickPos(&JOYSTICK);
		JOYSTICK_DIR = joyStickDir(&JOYSTICK);
	}
	
}

void menu(){
	menu_init();
		
	while(1){
		if(joyStickClick()){
			while(joyStickClick()){}
			//NAVIGATE TO SELCETED SUBMENU
			switch(MAIN_MENU.CURRENT_PAGE){
				case 0: //ENTER GAME SUBMENU
					game_menu();
					break;	
				case 1: //ENTER HIGHSCORE SUBMENU
					highscore_menu();
					break;	
				case 2: //ENTER SETTINGS
					settings_menu();
					break;	
				case 3: //PLAY CREDTIS
					OLED_credits();
					menu_init();
					break;	
			
			}
			
		}
		update_parameters(&MAIN_MENU);
		if(MAIN_MENU.MENU_CHANGE){
			OLED_reset();
			OLED_home();
			OLED_invert(MAIN_MENU.CURRENT_PAGE, main_menu_map[MAIN_MENU.CURRENT_PAGE]);	
			MAIN_MENU.MENU_CHANGE = 0;
		}	
	}
}

void game_menu(){
	GAME_MENU.CURRENT_PAGE = 0;
	OLED_reset();
	OLED_gamescreen();
	OLED_invert(GAME_MENU.CURRENT_PAGE, game_menu_map[0]);
	
	while(1){
		if(joyStickClick()){
			while(joyStickClick()){}
			//NAVIGATE TO SELCETED SUBMENU
			switch(GAME_MENU.CURRENT_PAGE){
				case 0: 
					play_game(&JOYSTICK, &SLIDER);
					break;
				
				case 1: //For further implementation
					break;
				
				case 2: //For further implementation
					break;
				
				case 3: //RETURN TO MAINMENU
					menu_init();
					return;
			}
		}
		
		update_parameters(&GAME_MENU);
		if(GAME_MENU.MENU_CHANGE){
			OLED_reset();
			OLED_gamescreen();
			OLED_invert(GAME_MENU.CURRENT_PAGE, game_menu_map[GAME_MENU.CURRENT_PAGE]);
			GAME_MENU.MENU_CHANGE = 0;
		}
	}
}

void settings_menu(){
	SETTINGS_MENU.CURRENT_PAGE = 0;
	OLED_reset();
	OLED_settingscreen();
	OLED_invert(SETTINGS_MENU.CURRENT_PAGE, settings_menu_map[0]);
	
	while(1){
		if(joyStickClick()){
			while(joyStickClick()){}
			//NAVIGATE TO SELCETED SUBMENU
			switch(SETTINGS_MENU.CURRENT_PAGE){
				case 0: //For further implementation
					break;
				
				case 1: //For further implementation
					break;
				
				case 2: //For further implementation
					break;
				
				case 3: //RETURN TO MAINMENU
					menu_init();
					return;
			}
		}
		
		update_parameters(&SETTINGS_MENU);
		if(SETTINGS_MENU.MENU_CHANGE){
			OLED_reset();
			OLED_settingscreen();
			OLED_invert(SETTINGS_MENU.CURRENT_PAGE, settings_menu_map[SETTINGS_MENU.CURRENT_PAGE]);
			SETTINGS_MENU.MENU_CHANGE = 0;
		}
	}
}

void highscore_menu(){
	HIGHSCORE_MENU.CURRENT_PAGE = 0;
	OLED_reset();
	OLED_highscorescreen();
	OLED_invert(HIGHSCORE_MENU.CURRENT_PAGE, highscore_menu_map[0]);
	
	while(1){
		if(joyStickClick()){
			while(joyStickClick()){}
			//NAVIGATE TO SELCETED SUBMENU
			switch(HIGHSCORE_MENU.CURRENT_PAGE){
				case 0: //For further implementation
					break;
				
				case 1: //For further implementation
					break;
				
				case 2: //For further implementation
					break;
				
				case 3: //RETURN TO MAINMENU
					menu_init();
					return;
			}
		}
		
		update_parameters(&HIGHSCORE_MENU);
		if(HIGHSCORE_MENU.MENU_CHANGE){
			OLED_reset();
			OLED_highscorescreen();
			OLED_invert(HIGHSCORE_MENU.CURRENT_PAGE, highscore_menu_map[HIGHSCORE_MENU.CURRENT_PAGE]);
			HIGHSCORE_MENU.MENU_CHANGE = 0;
		}
	}
}
