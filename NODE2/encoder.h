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

int32_t read_encoder(void);

static int32_t scale_encoder_value(int32_t value);




#endif /* ENCODER_H_ */