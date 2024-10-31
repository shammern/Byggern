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
#include "Common.h"



#ifndef ADC_H_
#define ADC_H_



void adc_init(void);
void adc_read(JoyStick *Stick, Slider *Slide);
void pos_calibrate(JoyStick *Stick);
void test_adc(JoyStick *Stick, Slider *Slide);
void joyStickPos(JoyStick *Stick);
Joystick_direction joyStickDir(JoyStick *Stick);
JoyStick* JoyStickInit(void); 
uint8_t joyStickClick(); //Denne m� nok sees p� senere n�r vi vet hvordan den skal implementeres, men den funker :)

#endif /* ADC_H_ */