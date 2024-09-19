/*
 * ADC.c
 *
 * Created: 19.09.2024 12:53:33
 *  Author: torstepu
 */ 
#include "ADC.h"
void adc_init(void){
	// Sett PD5 (OC1A) som utgang
	DDRD |= (1 << PD5);

	// Sett Timer/Counter1 til Fast PWM-modus, 8-bit
	// WGM12:0 = 011 (Fast PWM, 8-bit)
	// COM1A1:0 = 10 (Clear OC1A on compare match, set OC1A at BOTTOM)
	TCCR1A |= (1 << WGM10) | (1 << COM1A1);
	TCCR1B |= (1 << WGM12) | (1 << CS10); // Sett prescaler til 8
	
	

	// Sett initial PWM-verdi (duty cycle)
	OCR1A = 128; // 50% duty cycle
	
	
	
}
void test_adc(void){
	
	
	
}