/*
 * SERVO_driver.c
 *
 * Created: 30.10.2024 13:36:19
 *  Author: sigvesm
 */ 

#define LOWER_DUTY_LIMIT 0.05
#define UPPER_DUTY_LIMIT 0.1
#define X_MIN 0
#define X_MAX 200
#define GAIN (UPPER_DUTY_LIMIT-LOWER_DUTY_LIMIT)/X_MAX //Must be changed if X_min offset not equal 0
#define OFFSET (UPPER_DUTY_LIMIT + LOWER_DUTY_LIMIT)/2 


#include "servo_driver.h"

void servo_init(){
	PWM_init();
	//servo greier
}


void servo_set_pos(int pos){
	//WE DO THE REST TOMORROW :)
	
}