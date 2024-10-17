/*
 * ADC.h
 *
 * Created: 19.09.2024 12:53:54
 *  Author: torstepu
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "XMEM.h"



#ifndef ADC_H_
#define ADC_H_

typedef struct{
	uint8_t x_value;
	uint8_t y_value;
	int8_t x_percent;
	int8_t y_percent;
	uint8_t x_neutralPoint;
	uint8_t y_neutralPoint;	
} JoyStick;

typedef struct{
	uint8_t l_slider;
	uint8_t r_slider;
	int8_t l_slider_percent;
	int8_t r_slider_percent;
} Slider;

typedef enum{
	UP = 1,
	DOWN,
	RIGHT,
	LEFT,
	NEUTRAL
} Joystick_direction;

void adc_init(void);
void adc_read(JoyStick *Stick, Slider *Slide);
void pos_calibrate(JoyStick *Stick);
void test_adc(JoyStick *Stick, Slider *Slide);
void joyStickPos(JoyStick *Stick);
Joystick_direction joyStickDir(JoyStick *Stick);
JoyStick* JoyStickInit(void); 
uint8_t joyStickClick(); //Denne m� nok sees p� senere n�r vi vet hvordan den skal implementeres, men den funker :)

#endif /* ADC_H_ */