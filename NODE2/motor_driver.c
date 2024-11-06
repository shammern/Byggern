/*
 * motor_driver.c
 *
 * Created: 06.11.2024 10:19:51
 *  Author: torstepu
 */ 


#include "motor_driver.h"

void motor_init(void){
	
	//Enable PIOB pins to motor output
	PIOB->PIO_PER |= ENABLE | DIR;
	PIOB->PIO_OER |= ENABLE | DIR;
	
	//La inn initialiseringen for 
	PWM_set_duty(0, 0);
	

}

void motor_enable(void){}

void motor_disable(void){}
	


void set_motor_speed(int speed){
	
}



void set_motor_direction(int dir){
	
}



void drive_motor(int slider_val){
	
}


