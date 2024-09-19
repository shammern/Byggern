/*
 * ADC.h
 *
 * Created: 19.09.2024 12:53:54
 *  Author: torstepu
 */ 

#include <stdio.h>
#include <avr/io.h>


#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
volatile uint8_t adc_read(uint8_t channel); //Volatile
void pos_calibrate();
//pos_t pos_read(void);
void test_adc(void);



#endif /* ADC_H_ */