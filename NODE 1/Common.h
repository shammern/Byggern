/*
 * Common.h
 *
 * Created: 31.10.2024 10:00:03
 *  Author: torstepu
 */ 


#ifndef COMMON_H_
#define COMMON_H_

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

typedef struct{
	uint16_t msg_ID;
	uint8_t msg_length;
	uint8_t data[8];
} CAN_MESSAGE;

typedef enum {
	USER_INPUT = 1,
} CAN_MESSAGE_ID;




#endif /* COMMON_H_ */