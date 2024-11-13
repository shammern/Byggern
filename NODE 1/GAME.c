/*
 * GAME.c
 *
 * Created: 03.10.2024 13:55:10
 *  Author: danienes
 */ 
#include "GAME.h"

void play_game(JoyStick * stick, Slider *slide){
	while (1){
		get_user_input(stick, slide);
		send_user_input(stick, slide);
		if (slide->l_slider > 250){ //We are truly sorry for this implementation...
			return;
		}
	}
}



