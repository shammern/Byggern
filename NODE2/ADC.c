/*
 * ADC.c
 *
 * Created: 31.10.2024 10:36:17
 *  Author: torstepu
 */ 

#include "ADC.h"

void adc_init(void){
	//Set ADC to freerunmode
	ADC->ADC_MR = ADC_MR_FREERUN;
	
	//Enable channel 0
	ADC->ADC_CHER = ADC_CHER_CH0;
	
	//Enable PMC for ADC
	PMC->PMC_PCER1 |= 1 << (ID_ADC - 32);
	
	//Enable ADC conversion
	ADC->ADC_CR = ADC_CR_START;
	
}

//Possible interuptdriven goal tracking
void adc_init_interupt(void){
	PMC->PMC_PCER1 |= 1 << (ID_ADC - 32);
	ADC->ADC_MR = ADC_MR_TRGEN_DIS;
}


uint16_t adc_read(void){
	return ADC->ADC_CDR[0];	
}