/*
 * SPI.c
 *
 * Created: 10.10.2024 09:09:41
 *  Author: danienes
 */ 

#include "SPI.h"
#include <avr/io.h>

void SPI_init(void){
	// Set MOSI and SCK output, all others input 
	DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4);
	DDRB &= ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB3) & ~(1 << PB6); //BLODKOK
	// Enable SPI, Master, set clock rate fck/16 
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//SPDR |= ~(1<<CPOL) | ~(1<<CPHA); //Mulig feil
	PORTB |= (1<<PB4);
}

void SPI_write(char Data){
	//Start transmission 
	SPDR = Data;
	
	while(!(SPSR & (1<<SPIF))){
		// Wait for transmission complete
	}
	
}

uint8_t SPI_receive(void){
	SPI_write(0x00);
	
	return SPDR;
}

void SPI_slaveSelect(void){
	PORTB &= ~(1<<PB4);
}

 void SPI_slaveDeselect(void){
 	PORTB |= (1<<PB4);
 }

void SPI_test(void){
	SPI_write(0xaa);
	_delay_ms(10);
	SPI_write(0x00);
	_delay_ms(10);	
}