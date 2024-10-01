/*
 * UART_INTERFACE.c
 *
 * Created: 09.09.2024 10:56:48
 * Author : torstepu
 */ 

#include "UART.h"


void USART_Init(unsigned int ubrr ){
	UBRR0H = (unsigned char)(ubrr>>8);	// Set baud rate 
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);		// Enable receiver and transmitter 
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);	// Set frame format: 8data, 2stop bit 
	
}


int uart_putchar(char c, FILE *stream) {
	if (c == '\n') {
		uart_putchar('\r', stream);  // Send carriage return before newline
	}
	// Wait to sending buffer is ready
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
	return 0;
}


// Function for reading a single char via UART
int uart_getchar(FILE *stream) {
	// Wait to a databyte is ready
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

// Function to set op printf
void uart_setup_stdio(void) {
	// Redirect stdout to UART with fdevopen
	FILE *uart_stdout = fdevopen(uart_putchar, NULL);
	if (uart_stdout != NULL) {
		stdout = uart_stdout;  // Redirects printf to UART
	}
}

/*
int main(void) {
	USART_Init(MYUBRR);

	uart_setup_stdio();

	printf("UART kommunikasjon er klar!\n");

	for(int i = 0; i < 10; i++) {
		
		printf("Teller: %d\n", i);
		_delay_ms(1000);  
	}
}
	*/
	
