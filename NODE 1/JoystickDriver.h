/*
 * JoystickDriver.h
 *
 * Created: 24.10.2024 13:34:19
 *  Author: danienes
 */ 


#include "ADC.h"
#include "CAN.h"

#ifndef JOYSTICKDRIVER_H_
#define JOYSTICKDRIVER_H_


void send_user_input(JoyStick *stick, Slider *slide);
void get_user_input(JoyStick *stick, Slider *slide);


#endif /* JOYSTICKDRIVER_H_ */