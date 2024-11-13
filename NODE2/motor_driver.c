/*
 * motor_driver.c
 *
 * Created: 06.11.2024 10:19:51
 *  Author: torstepu
 */ 


#include "motor_driver.h"
#include <stdlib.h>

#define MAX_SPEED 100
#define MIN_SPEED 0 



void motor_init(void){	
	//Enable PIOB pins to motor output
	
	PIOC->PIO_OER |= DIR;
	PIOC->PIO_PER |= DIR;
	
	PWM_set_duty(0, 0);	
}


void set_motor_speed(float speed){
	speed = abs(speed);
	if (speed > MAX_SPEED){
		return;
	}
	float D = (float)speed/100; //Converts speed to duty cycle
	PWM_set_duty(D, 0);
}



void set_motor_direction(int direction){
	if(direction > 0){
		PIOC->PIO_CODR = DIR;	//Left
	}
	else if(direction <= 0){
		PIOC->PIO_SODR = DIR; //right
	}
	else{
		printf("Invalid direction!!\n");
	}
}


void drive_motor_joystick(int x_value){
	uint32_t encoder_value = read_encoder();
	int current_pos = scale_encoder_joystick(encoder_value);
	float u = pid_controller(x_value, current_pos);
	set_motor_direction(u);
	set_motor_speed(u);
}


void drive_motor_slider(int slider_val){
	//PID not tuned to use slider as input -> bad performance
	uint32_t encoder_value = read_encoder();
	int current_pos = scale_encoder_value(encoder_value);
	
	float u = pid_controller(slider_val, current_pos);	
	set_motor_direction(u); 
	set_motor_speed(u);
	
}
	


