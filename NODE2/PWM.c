/*
 * PWM.c
 *
 * Created: 30.10.2024 10:27:53
 *  Author: sigvesm
 */ 

#include "PWM.h"

#define MCK 84E6	// 84MHz
#define PWM_FREQ 50 // 50Hz
#define PWM_T 20E-3 // 20ms
#define PWM_T_B 1E-4

#define DIVA 84
#define CLK_A 1E6
#define CPRDA (int)(PWM_T*MCK/DIVA)

#define DIVB 84
#define CLK_B 1E6
#define CPRDB (int)(PWM_T_B*MCK/DIVB)


void PWM_init(){
	PIOB->PIO_ABSR |= PIO_PB12B_PWMH0 | PIO_PB13B_PWMH1 ;  //Enables PWM module on PIO controller C function B. Pin 44/45
	
	PIOB->PIO_PDR |= PIO_PB12B_PWMH0 | PIO_PB13B_PWMH1; //Disable PIO controller for controlling PWM pins
	
	PWM->PWM_DIS = PWM_DIS_CHID0;
	PWM->PWM_DIS = PWM_DIS_CHID1;  //Disables PWM on channel 1
	
	PMC->PMC_PCER1 |= 1 << (ID_PWM - 32); //Enables peripheral clock for PWM
	
	PWM->PWM_CLK |= PWM_CLK_PREA(0) | PWM_CLK_DIVA(DIVA); //Sets PWM clock A
	PWM->PWM_CLK |= PWM_CLK_PREB(0) | PWM_CLK_DIVB(DIVB); //Sets PWM clock B
	
	// Configure PWM channel mode for left-aligned mode, non-inverted
	PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_CLKB;  // Use PWM clock A
	PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_CLKA;  // Use PWM clock A
	
	
	PWM->PWM_CH_NUM[0].PWM_CPRD = PWM_CPRD_CPRD(CPRDB);
	PWM->PWM_CH_NUM[1].PWM_CPRD = PWM_CPRD_CPRD(CPRDA); //Sets PWM Periode for clock A
	
	
	PWM->PWM_ENA = PWM_DIS_CHID0;	
	PWM->PWM_ENA = PWM_DIS_CHID1; //Enables PWM on channel 1
	
}



void PWM_set_duty(float duty_cycle, uint8_t channel){
	if(duty_cycle < 0 || duty_cycle > 1){
		return;
	}
	int D = 0;
	D = (int) (PWM->PWM_CH_NUM[channel].PWM_CPRD*(1-duty_cycle));
	PWM->PWM_CH_NUM[channel].PWM_CDTY = PWM_CDTY_CDTY(D);	
}


void PWM_set_freq(int freq, uint8_t channel){
	//DO WE NEED THIS?
}


