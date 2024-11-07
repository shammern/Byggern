/*
 * solenoide.c
 *
 * Created: 07.11.2024 12:48:27
 *  Author: danienes
 */ 

#include "solenoide.h"

void solenoide_init(void){
	PMC->PMC_PCER0 |= (1 << ID_PIOA);	
	
	//INIT solenoide pin as output and set default value to 0
	PIOA->PIO_OER |= SOLENOIDE_ID;
	PIOA->PIO_PER |= SOLENOIDE_ID;
	PIOA->PIO_SODR |= SOLENOIDE_ID;
	
}



void run_solenoide(int run){
	if (run){
		PIOA->PIO_CODR |= SOLENOIDE_ID;
		//time_spinFor(msecs(200));
		
	}else{
		PIOA->PIO_SODR |= SOLENOIDE_ID;
	}
}