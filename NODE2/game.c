/*
 * game.c
 *
 * Created: 31.10.2024 14:24:02
 *  Author: torstepu
 */ 

#include "game.h"
#include "time.h"

#define THRESHOLD 3000
#define TIME_THRESHOLD msecs(1000)
static int TIME = 0;
static int THRESHOLD_FLAG = 0;

uint8_t goal_register(){
	int value = 0;
	value = adc_read();
	
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
		THRESHOLD_FLAG = 0;
	}
	return 0;
}