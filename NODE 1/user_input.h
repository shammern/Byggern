/*
 * user_input.h
 *
 * Created: 31.10.2024 09:35:20
 *  Author: torstepu
 */ 

#include "ADC.h"
#include "CAN.h"

#ifndef USER_INPUT_H_
#define USER_INPUT_H_


void send_user_input(JoyStick *stick, Slider *slide);
void get_user_input(JoyStick *stick, Slider *slide);

#endif /* USER_INPUT_H_ */