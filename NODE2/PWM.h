/*
 * PWM.h
 *
 * Created: 30.10.2024 10:28:17
 *  Author: sigvesm
 */ 
#include <stdio.h>
#include "sam.h"


#ifndef PWM_H_
#define PWM_H_

void PWM_init();
void PWM_set_duty(float duty_cycle, uint8_t channel);



#endif /* PWM_H_ */