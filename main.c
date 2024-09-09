/*
 * UART_INTERFACE.c
 *
 * Created: 09.09.2024 10:56:48
 * Author : torstepu
 */ 
#define F_CPU 4915200 //Clock-Speed
#define USART_BAUDRATE 9600
#define MYUBRR F_CPU/USART_BAUDRATE/16 - 1//(((F_CPU/(USART_BAUDRATE*16U)))-1)

#include <avr/io.h>
#include <unistd.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


void USART_Init(unsigned int ubrr ){
	UBRR0H = (unsigned char)(ubrr>>8);	// Set baud rate 
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);		// Enable receiver and transmitter 
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);	// Set frame format: 8data, 2stop bit 
	
}
/*
int USART_Transmit(unsigned char data){
	while (!( UCSR0A & (1<<UDRE0)));		// Wait for empty transmit buffer 
	
	UDR0 = data;	// Put data into buffer, sends the data 
	return 0;		
}

unsigned char USART_Receive(void){
	
	while (!(UCSR0A & (1<<RXC0)));	// Wait for data to be received 
	
	return UDR0;	// Get and return received data from buffer 
}

void USART_SendString(char *str){
	unsigned char j = 0;
	while(str[j] != 0){
		USART_Transmit(str[j]);
		j++;
	}
}


void USART_Flush( void ){
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}
*/

int uart_putchar(char c, FILE *stream) {
	if (c == '\n') {
		uart_putchar('\r', stream);  // Send carriage return før newline
	}
	// Vent til sendebufferet er klart
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
	return 0;
}

// Funksjon for å lese en enkelt karakter via UART (hvis ønskelig)
int uart_getchar(FILE *stream) {
	// Vent til en data byte er mottatt
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

// Funksjon for å sette opp UART til bruk med printf ved hjelp av fdevopen()
void uart_setup_stdio(void) {
	// Omdiriger stdout til UART ved hjelp av fdevopen
	FILE *uart_stdout = fdevopen(uart_putchar, NULL);
	if (uart_stdout != NULL) {
		stdout = uart_stdout;  // Omdiriger printf til UART
	}
}
/*

int main(void){

	//char c;
	USART_Init(31);
	uart_setup_stdio();
	
	printf("Testing:");
	
	//USART_SendString("ECHO");
	while (1){
		//c=USART_Receive();
		printf("Teller: %d\n", 123);
		_delay_ms(200);
	}
}*/

int main(void) {
	// Initialiser UART med riktig baudrate
	USART_Init(MYUBRR);

	// Sett opp printf til å bruke UART via fdevopen()
	uart_setup_stdio();

	// Test printf-funksjonen
	printf("UART kommunikasjon er klar!\n");

	for(int i = 0; i < 10; i++) {
		// Test: skriv ut en verdi via UART
		printf("Teller: %d\n", i);
		_delay_ms(1000);  // Vent ett sekund
	}
}
	
	


/*
void UART_init(long USART_BAUDRATE){
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0); //Enable tx/rx
	UCSR0C |= (1<<URSEL0) | (1<<UCSZ00) | (1<<UCSZ10); //Set 8-bit char size
	UBRR0L = BAUD_PRESCALE: //Set lower 8-bit of the baudrate
	UBRR0H = (BAUD_PRESCALE >> 8); //Set upper 8-bits
}
*/
