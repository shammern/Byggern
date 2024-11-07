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
	
	//PMC->PMC_PCER0 |= (1 << ID_PIOC);
	
	//Enable PIOB pins to motor output
	
	PIOC->PIO_OER |= DIR;
	PIOC->PIO_PER |= DIR;
	
	//La inn initialiseringen for PB12 pinnen for PWM, channel 0
	PWM_set_duty(0, 0);
	

}

void motor_enable(void){}

void motor_disable(void){}
	


void set_motor_speed(float speed){
	speed = abs(speed);
	if (speed > MAX_SPEED || speed < MIN_SPEED){
		printf("INVALID SERVO POSITION: %f\n", speed);
		return;
	}
	float D = (float)speed/100;
	PWM_set_duty(D, 0);
}



void set_motor_direction(int direction){
	if(direction > 0){
		PIOC->PIO_CODR = DIR;	//Left
	}
	else if(direction <= 0){
		PIOC->PIO_SODR = DIR;
	}
	else{
		printf("Invalid direction!!\n");
	}
}


void drive_motor_joystick(int x_value){
	uint32_t encoder_value = read_encoder();
	int current_pos = scale_encoder_joystick(encoder_value);
	printf("Current x_pos: %d\n ", current_pos);
	int u = motor_position_controller(encoder_value, x_value);
	printf("SIUUUUUUUUUUUUUUU: %d \n", u);
	set_motor_direction(x_value);
	set_motor_speed(u);
}


void drive_motor_slider(uint8_t slider_val){
	uint32_t encoder_value = read_encoder();
	uint8_t current_pos = scale_encoder_value(encoder_value);
	printf("Current_pos: %d\n ", current_pos);
	float u = pid_controller(slider_val, current_pos);
	printf("SIIUUUUUUUUUUUUUUUUUU: %f\n ", u);
	
	if (u < 0){
		set_motor_direction(1); //Left
		set_motor_speed(u);
		printf("DRIVING LEFT\n");
	}
	else{
		set_motor_direction(-1); //Right
		set_motor_speed(u);
		printf("DRIVING RIGHT\n");
	}
}


