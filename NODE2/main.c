/*
 * NODE2.c
 *
 * Created: 17.10.2024 09:19:56
 * Author : sigvesm
 */ 


#include "sam.h"
#include "uart.h"
#include "can.h"


void configure_pin(void) {
	// Step 1: Enable the clock for PIOB
	PMC->PMC_PCER0 |= (1 << ID_PIOB);

	// Step 2: Set PB13 as output
	PIOB->PIO_OER |= (1 << 13);   // Set PB13 to output
	PIOB->PIO_PER |= (1 << 13);   // Enable control of PB13 by PIOB

	// Step 3: Set PB13 high
	PIOB->PIO_SODR |= (1 << 13);  // Set PB13 high
}


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	uart_init();
	

    /* Replace with your application code */
	
	can_init(0);
	
	CanMsg message;
	
	message.id = 100;
	message.length = 8;
	message.byte[0] = 0xFF;
	message.byte[1] = 0x22;
	message.byte[2] = 0x33;
	message.byte[3] = 0x44;
	message.byte[4] = 0x55;
	message.byte[5] = 0x66;
	message.byte[6] = 0x77;
	message.byte[7] = 0x88;

	
    while (1) 
    {
		can_tx(message);
    }
}
