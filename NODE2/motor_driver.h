/*
 * motor_driver.h
 *
 * Created: 06.11.2024 10:19:34
 *  Author: torstepu
 */ 



#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include "sam.h"
#include <stdio.h>
#include "PWM.h"
#include "PID.h"
#include <stdlib.h>
#include "encoder.h"


#define ENABLE	PIO_PB12
#define DIR		PIO_PC23


void motor_init(void);

void motor_enable(void);

void motor_disable(void);

void set_motor_speed(float speed);

void set_motor_direction(int dir);

void drive_motor_joystick(int x_value);

void drive_motor_slider(uint8_t slider_val);



#endif /* MOTOR_DRIVER_H_ */