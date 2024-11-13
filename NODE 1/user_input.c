/*
 * user_input.c
 *
 * Created: 31.10.2024 09:35:34
 *  Author: torstepu
 */ 

#include "user_input.h"

void send_user_input(JoyStick *stick, Slider *slide){

//Make CAN message
//MSG type = USER_INPUT
//MSG length = 8
//data[0] = joystick x percent (int, must be converted)
//data[1] = joystick y percent (int, must be converted)
//data[2] = joystick pos
//data[3] = joystick click
//data[4] = left button (not implementet)
//data[5] = right button (not implementet)
//data[6] = left slider value (can be changed to percent)
//data[7] = right slider value (can be changed to percent)

CAN_MESSAGE message;
message.msg_ID = USER_INPUT;
message.msg_length = 8; 
message.data[0] = (uint8_t)stick->x_percent+100;
message.data[1] = (uint8_t)stick->y_percent+100;
message.data[2] = (uint8_t)joyStickDir(stick);
message.data[3] = joyStickClick();
message.data[4] = 0; //To be implemented
message.data[5] = 0; //To be implemented
message.data[6] = slide->l_slider;
message.data[7] = slide->r_slider;

CAN_transmit(&message);
}

void get_user_input(JoyStick *stick, Slider *slide){
	adc_read(stick, slide);
	joyStickPos(stick);
}