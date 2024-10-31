/*
 * NODE2.c
 *
 * Created: 17.10.2024 09:19:56
 * Author : sigvesm
 */ 

#define F_CPU 84000000
#define UART_BAUDRATE 9600
#include <stdio.h>
#include "sam.h"
#include "uart.h"
#include "can.h"
#include "time.h"
#include "PWM.h"
#include "SERVO_driver.h"
#include "ADC.h"
#include "game.h"
static unsigned int GOAL_COUNT;



// void configure_pin(void) {
// 	// Step 1: Enable the clock for PIOB
// 	PMC->PMC_PCER0 |= (1 << ID_PIOB);
// 
// 	// Step 2: Set PB13 as output
// 	PIOB->PIO_PER |= (1 << 13);   // Enable control of PB13 by PIOB
// 	PIOB->PIO_OER |= (1 << 13);   // Set PB13 to output
// 	
// 	// Step 3: Set PB13 high
// 	PIOB->PIO_CODR |= (1 << 13);  // Set PB13 LOW
// 	//PIOB->PIO_SODR |= (1 << 13);  // Set PB13 HIGH
// 	
// }


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disables the watchdog timer
	uart_init(F_CPU, UART_BAUDRATE);
	can_init(1);
	printf("\n-----------------------PROGRAM START------------------------\n");
	//CanMsg m;
	servo_init();
	adc_init();
	uint8_t update_value;
	while(1){
	update_value = goal_register();
	
	if (update_value){
		GOAL_COUNT ++;
	}
	printf("GOAL COUNT IS: %d\n", GOAL_COUNT);
		
	}
}
