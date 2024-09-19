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

#define BASE_ADDRESS 0x1000

void xmem_init(void);

void xmem_write(uint8_t data, uint16_t addr);

uint8_t xmem_read(uint16_t addr);


#endif /* XMEM_H */