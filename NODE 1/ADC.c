/*
 * ADC.c
 *
 * Created: 19.09.2024 12:53:33
 *  Author: torstepu
 */ 
#include "ADC.h"

void adc_init(void){
	// Set PD5 (OC1A) as output
	DDRD |= (1 << PD5);

	// COM1A1:0 = 10 (Clear OC1A on compare match, set OC1A at BOTTOM)
	TCCR1A |= (1 << WGM10) | (1 << WGM11) | (1 << COM1A0) ;
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10); // Set prescaler to 8
		
	//Configure buttons
	DDRD &= ~(1 << PD4);  //Set PD4 as input
	PORTB |= (1 << PD4);  // Enable pull-up resistor on PD4
}

void adc_read(JoyStick *Stick, Slider *slide){
	xmem_write(1, XMEM_ADC);
	_delay_us(15);
	Stick->y_value = xmem_read(XMEM_ADC);
	Stick->x_value = xmem_read(XMEM_ADC);
	slide->l_slider = xmem_read(XMEM_ADC);
	slide->r_slider = xmem_read(XMEM_ADC);
	_delay_ms(50); //delay to ensure all values are read correctly
}



void test_adc(JoyStick *Stick, Slider *Slide){
	adc_read(Stick, Slide);
	joyStickPos(Stick);
	printf("------------------------------------\n");
	printf("The X-Value is : %d\n", Stick->x_value);
	printf("The Y-Value is : %d\n", Stick->y_value);
	
	joyStickDir(Stick);
	printf("The X-per is : %d\n", Stick->x_percent);
	printf("The Y-per is : %d\n", Stick->y_percent);	
	
	printf("The Right slider value is : %d\n",Slide->r_slider);
	printf("The Left slider value is : %d\n",Slide->l_slider);
	printf("Y NEUTRAL IS : %d\n", Stick->y_neutralPoint);
	printf("X NEUTRAL IS : %d\n", Stick->x_neutralPoint);		
}

void joyStickPos(JoyStick *Stick){
	//Updates X values
	uint8_t x_neutral = Stick->x_neutralPoint;
	uint8_t y_neutral = Stick->y_neutralPoint;
	
	if (Stick->x_value>x_neutral+10){
		Stick->x_percent = ((int16_t)(Stick->x_value - x_neutral) * 100) / (255 - x_neutral);
	}
	else if (Stick->x_value< x_neutral-10){
		Stick->x_percent = ((int16_t)(Stick->x_value - x_neutral) * 100) / x_neutral;
	}
	
	else{
		Stick->x_percent = 0;
	}
	//updates Y values
	if (Stick->y_value>y_neutral+10){
		Stick->y_percent = ((int16_t)(Stick->y_value - y_neutral) * 100) / (255 - y_neutral);
	}
	else if (Stick->y_value<y_neutral-10){
		Stick->y_percent = ((int16_t)(Stick->y_value - y_neutral) * 100) / y_neutral;
	}		
	
	else{
		Stick->y_percent = 0;
	}
}


Joystick_direction joyStickDir(JoyStick *Stick){
	uint8_t x = abs(Stick->x_percent);
	uint8_t y = abs(Stick->y_percent);
	if (x>y){
		if (Stick->x_percent>50){ //Added margins for debouncing
			return RIGHT;
		}
		else if(Stick->x_percent<-50){
			return LEFT;
		}
		else{
			return NEUTRAL;			
		}	
	}
	else if (x<y){
		if (Stick->y_percent>50){
			return UP;
		}
		else if(Stick->y_percent<-50){
			return DOWN;
		}
		else{
			return NEUTRAL;		
		}
	}
	else{
		return NEUTRAL;	
	}
}

void pos_calibrate(JoyStick *Stick){
	xmem_write(1, XMEM_ADC);
	_delay_us(15);
	Stick->x_neutralPoint = xmem_read(XMEM_ADC);
	Stick->y_neutralPoint = xmem_read(XMEM_ADC);
}

uint8_t joyStickClick(){
	if ((PIND & (1 << PD4)) == 0) {
		return 1;
	}
	return 0;
}