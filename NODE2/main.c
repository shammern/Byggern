/*
 * NODE2.c
 *
 * Created: 17.10.2024 09:19:56
 * Author : sigvesm
 */ 

#define F_CPU 84000000
#define UART_BAUDRATE 9600
#include <stdio.h>
#include <stdint.h>
#include "sam.h"
#include "uart.h"
#include "can.h"
#include "time.h"
#include "PWM.h"
#include "SERVO_driver.h"
#include "ADC.h"
#include "game.h"
#include "encoder.h"
#include "solenoide.h"

static unsigned int GOAL_COUNT;


void full_init(){
	 SystemInit();
	 WDT->WDT_MR = WDT_MR_WDDIS; //disables the watchdog timer
	 uart_init(F_CPU, UART_BAUDRATE);
	 can_init(1);
	 encoder_init();
	 servo_init();
	 adc_init();
	 motor_init();
	 solenoide_init();
}


int main(void)
{
    /* Initialize the SAM system */
    full_init();
	printf("\n-----------------------PROGRAM START------------------------\n");
	
	while(1){
 		
		uint8_t update = goal_register();
		if (update == 1){
			GOAL_COUNT += update;
			printf("CURRENT GOAL COUNT: %d\n", GOAL_COUNT);
			time_spinFor(msecs(2000));
		}	

//  		GOAL_COUNT += goal_register();
//  		printf("CURRENT GOAL COUNT: %d\n", GOAL_COUNT);
	}
}
