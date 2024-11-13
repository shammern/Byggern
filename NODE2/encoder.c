/*
 * encoder.c
 *
 * Created: 06.11.2024 11:41:48
 *  Author: torstepu
 */ 

#include "encoder.h"

#define QUAD_A	PIO_PC25
#define QUAD_B	PIO_PC26

#define ENCODER_MAX 5580
#define ENCODER_MIN 0
#define SLIDER_MAX 255
#define JOYSTICK_MIN -100
#define JOYSTICK_MAX 100


void encoder_init(void){
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	//Enable clock register for TC2
	
	PMC->PMC_PCER1 |= (1 << (ID_TC6 - 32)); 
	
	PIOC->PIO_PDR |= QUAD_A | QUAD_B;      
	PIOC->PIO_ABSR |= QUAD_A | QUAD_B;
	
	//Disable clock for channel 0 in TC2 under the setup
	TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;
	
	//Set quadrature mode
	TC2->TC_BMR |= TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA; 
	
	//Set XC0 as clock
	TC2->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_XC0; 
	
	//Enable TC2
	TC2->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG | TC_CCR_CLKEN;
	
}


int scale_encoder_value(uint32_t encoder_value){
	//Scales encoder values for use with slider
	return (int)(SLIDER_MAX * encoder_value / (ENCODER_MAX - ENCODER_MIN));
}  

int scale_encoder_joystick(uint32_t encoder_value) {
	// Scale encoder_value to range [-100, 100]
	return JOYSTICK_MIN + (encoder_value - ENCODER_MIN) * (JOYSTICK_MAX - JOYSTICK_MIN) / (ENCODER_MAX - ENCODER_MIN);
}                                                                                                                                                                                                                                                                                           


uint32_t read_encoder(void){
	return TC2->TC_CHANNEL[0].TC_CV;
}
