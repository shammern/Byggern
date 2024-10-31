/*
 * ADC.h
 *
 * Created: 31.10.2024 10:36:31
 *  Author: torstepu
 */ 
#pragma once

#include "sam.h"

#ifndef ADC_H_
#define ADC_H_

void adc_init(void);

uint16_t adc_read(void);



#endif /* ADC_H_ */