/*
 * UART.h
 *
 * Created: 12.09.2024 09:23:21
 *  Author: torstepu
 */ 


#ifndef UART_H
#define UART_H

#define F_CPU 4915200 //Clock-Speed
#define USART_BAUDRATE 9600
#define MYUBRR F_CPU/USART_BAUDRATE/16 - 1//(((F_CPU/(USART_BAUDRATE*16U)))-1)

#include <avr/io.h>
#include <unistd.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

void USART_Init(unsigned int ubrr);

int uart_putchar(char c, FILE *stream);

int uart_getchar(FILE *stream);

void uart_setup_stdio(void);



#endif /* INCFILE1_H_ */