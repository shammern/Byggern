/*
 * XMEM.h
 *
 * Created: 12.09.2024 13:15:45
 *  Author: torstepu
 */ 

#include <avr/io.h>
#include <stdio.h>

#ifndef XMEM_H
#define XMEM_H

#define XMEM_OLED_CMD 0x1000
#define XMEM_OLED_DATA 0x1200
#define XMEM_ADC 0x1400
#define XMEM_SRAM 0x1800

void xmem_init(void);

void xmem_write(int8_t data, uint16_t addr);
int8_t xmem_read(uint16_t addr);


#endif /* XMEM_H */