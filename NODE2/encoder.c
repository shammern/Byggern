/*
 * encoder.c
 *
 * Created: 06.11.2024 11:41:48
 *  Author: torstepu
 */ 

#include "encoder.h"

#define QUAD_A	PIO_PC25
#define QUAD_B	PIO_PC26

void encoder_init(void){
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	//Enable clock register for TC2
	//PMC->PMC_PCER1 |= (1 << ID_TC2);
	PMC->PMC_PCER1 |= (1 << (ID_TC6 - 32)); 
	
	PIOC->PIO_PDR |= QUAD_A | QUAD_B;      
	PIOC->PIO_ABSR |= QUAD_A | QUAD_B;
	
	//Disable clock for channel 0 in TC2 under the setup
	TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;
	
	TC2->TC_BMR |= TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA; 
	
	TC2->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_XC0; 
	
	TC2->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG | TC_CCR_CLKEN;
	
}


static int32_t scale_encoder_value(int32_t value){

}


int32_t read_encoder(void){
	return TC2->TC_CHANNEL[0].TC_CV;
}
