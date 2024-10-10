/*
 * XMEM.h
 *
 * Created: 12.09.2024 13:15:45
 *  Author: torstepu
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "GlobVariabel.h"

#ifndef XMEM_H
#define XMEM_H

void xmem_init(void);

void xmem_write(int8_t data, uint16_t addr);
int8_t xmem_read(uint16_t addr);


#endif /* XMEM_H */