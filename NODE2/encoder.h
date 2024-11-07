/*
 * encoder.h
 *
 * Created: 06.11.2024 11:41:36
 *  Author: torstepu
 */ 
#include "sam.h"
#include <stdint.h>

#ifndef ENCODER_H_
#define ENCODER_H_


void encoder_init(void);

uint32_t read_encoder(void);

uint8_t scale_encoder_value(uint32_t encoder_value);

int scale_encoder_joystick(uint32_t encoder_value);


#endif /* ENCODER_H_ */