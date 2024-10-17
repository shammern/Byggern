#include "joystickdriver.h"

void send_user_input(void){
    //Create joytstick and slider
    Joystick stick;
    Slider slide;

    //Get joystickpos
    adc_read(&stick, &slide);
    joystickPos(&stick);

    //Make CAN message
    //MSG type = USER_INPUT
    //MSG length = 8
    //data[0] = joystick x percent (int, must be converted)
    //data[1] = joystick y percent (int, must be converted)
    //data[2] = joystick pos
    //data[3] = joystick click
    //data[4] = left button
    //data[5] = right button
    //data[6] = left slider value (can be changed to percent)
    //data[7] = right slider value (can be changed to percent)

    CAN_MESSAGE message;
    message.msg_ID = USER_INPUT;
    message.msg_length = 8 //byte, men tar denne byte eller bit?
    message.data[0] = stick.x_percent;
    message.data[1] = stick.y_percent;
    message.data[2] = (uint8_t)joyStickDir(&stick);
    message.data[3] = joyStickClick();
    message.data[4] = 0; //To be implemented
    message.data[5] = 0; //To be implemented
    message.data[6] = slider.l_slider;
    message.data[7] = slider.r_slider0; 

    //send pos over CAN to correct cannode
    CAN_transmit(&message);
}