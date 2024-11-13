/*
 * game.c
 *
 * Created: 31.10.2024 14:24:02
 *  Author: torstepu
 */ 

#include "game.h"
#include "time.h"

#define THRESHOLD 300
#define TIME_THRESHOLD msecs(2000)
static int TIME = 0;
static int THRESHOLD_FLAG = 0;

uint8_t goal_register(){
	uint16_t value = 0;
	value = adc_read();
	//checks if conditions to update goalcount is met
	if (value < THRESHOLD && !THRESHOLD_FLAG){
		int TIME_NOW = time_now();
		if (TIME_NOW - TIME < TIME_THRESHOLD){
			return 0;
		}
		TIME = TIME_NOW;
		THRESHOLD_FLAG = 1;
		return 1;		
	}
	else if (value > THRESHOLD){
// 		int TIME_NOW = time_now();
// 		if (TIME_NOW - TIME < TIME_THRESHOLD){
// 			return 0;
// 		}
		THRESHOLD_FLAG = 0;
	}
	return 0;
}