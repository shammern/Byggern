/*
 * GlobVariabel.h
 *
 * Created: 03.10.2024 13:11:02
 *  Author: danienes
 */ 


#ifndef GLOBVARIABEL_H_
#define GLOBVARIABEL_H_

#define F_CPU 4915200 //Clock-Speed
#define F_CPU_CAN 16000000 //Clock-Speed CAN controller
#define USART_BAUDRATE 9600
#define MYUBRR F_CPU/USART_BAUDRATE/16 - 1

#define XMEM_OLED_CMD 0x1000
#define XMEM_OLED_DATA 0x1200
#define XMEM_ADC 0x1400
#define XMEM_SRAM 0x1800

#define PADDING 8
#define FONT_SIZE 8





#endif /* GLOBVARIABEL_H_ */