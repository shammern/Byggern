/*
 * UART.h
 *
 * Created: 12.09.2024 09:23:21
 *  Author: torstepu
 */ 

#include "GlobVariabel.h"
#include <avr/io.h>
#include <unistd.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#ifndef UART_H
#define UART_H

void USART_Init(unsigned int ubrr);

int uart_putchar(char c, FILE *stream);

int uart_getchar(FILE *stream);

void uart_setup_stdio(void);



#endif /* INCFILE1_H_ */