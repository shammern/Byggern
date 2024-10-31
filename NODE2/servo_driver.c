/*
 * SERVO_driver.c
 *
 * Created: 30.10.2024 13:36:19
 *  Author: sigvesm
 */ 

#define LOWER_DUTY_LIMIT 0.05
#define UPPER_DUTY_LIMIT 0.1
#define X_MIN -100
#define X_MAX 100
#define GAIN -(UPPER_DUTY_LIMIT-LOWER_DUTY_LIMIT)/(X_MIN-X_MAX)
#define OFFSET (UPPER_DUTY_LIMIT + LOWER_DUTY_LIMIT)/2 

#include "servo_driver.h"

void servo_init(){
	printf("SERVO INIT START\n");
	PWM_init();
	PWM_set_duty(0.075, 1);
	printf("SERVO INIT DONE\n");
}


void servo_set_pos(int pos){
	if (pos < X_MIN || pos > X_MAX ){
		printf("INVALID SERVO POSITION: %d\n", pos);
		return;
	}
	float D = (OFFSET + pos * GAIN);
	PWM_set_duty(D, 1);
}