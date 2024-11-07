/*
 * solenoide.h
 *
 * Created: 07.11.2024 12:48:07
 *  Author: danienes
 */ 

#include "time.h"
#include "sam.h"

#ifndef SOLENOIDE_H_
#define SOLENOIDE_H_

#define SOLENOIDE_ID PIO_PA10; //PA10 | D19

void solenoide_init(void);
void run_solenoide(int run);


#endif /* SOLENOIDE_H_ */