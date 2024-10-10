/*
 * SPI.h
 *
 * Created: 10.10.2024 09:09:24
 *  Author: danienes
 */ 


#include <stdio.h>
#include "GlobVariabel.h"
#include <util/delay.h>

#ifndef SPI_H_
#define SPI_H_

void SPI_init(void);
void SPI_write(char Data);
uint8_t SPI_read(void);
void SPI_slaveSelect(void);
void SPI_slaveDeselect(void);
void SPI_test(void);


#endif /* SPI_H_ */