/*
 * ADC.c
 *
 * Created: 19.09.2024 12:53:33
 *  Author: torstepu
 */ 
#include "ADC.h"
void adc_init(void){
	// Sett PD5 (OC1A) som utgang
	DDRD |= (1 << PD5);

	// Sett Timer/Counter1 til Fast PWM-modus, 8-bit
	// WGM12:0 = 011 (Fast PWM, 8-bit)
	// COM1A1:0 = 10 (Clear OC1A on compare match, set OC1A at BOTTOM)
	TCCR1A |= (1 << WGM10) | (1 << WGM11) | (1 << COM1A0) ;
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10); // Sett prescaler til 8
		
	//Configure buttons
	
	DDRD &= ~(1 << PD4);  //Set PD4 som input
	PORTB |= (1 << PD4);  // Enable pull-up resistor on PB1
	
	/*
	DDRD &= ~(1 << PD0);  // Set PD0 as input
	DDRB &= ~(1 << PB1);  // Set PB1 as input
	PORTD |= (1 << PD0);  // Enable pull-up resistor on PD0
	PORTB |= (1 << PB1);  // Enable pull-up resistor on PB1
	*/
}

void adc_read(uint16_t channel, JoyStick *Stick, Slider	*slide){
	xmem_write(1, channel);
	_delay_us(15);
	Stick->y_value = xmem_read(channel);
	Stick->x_value = xmem_read(channel);
	slide->l_slider = xmem_read(channel);
	slide->r_slider = xmem_read(channel);
}



void test_adc(JoyStick *Stick, Slider *Slide){
	//JoyStick Stick;
	//pos_calibrate(&Stick);
	adc_read(0x400, Stick, Slide);
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
	
	if (Stick->x_value>x_neutral+5){
		Stick->x_percent = ((int16_t)(Stick->x_value - x_neutral) * 100) / (255 - x_neutral);
	}
	else if (Stick->x_value< x_neutral-5){
		Stick->x_percent = ((int16_t)(Stick->x_value - x_neutral) * 100) / x_neutral;
	}
	
	else{
		Stick->x_percent = 0;
	}
	//updates Y values
	if (Stick->y_value>y_neutral+5){
		Stick->y_percent = ((int16_t)(Stick->y_value - y_neutral) * 100) / (255 - y_neutral);
	}
	else if (Stick->y_value<y_neutral-5){
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
		if (Stick->x_percent>0){
			printf("\nRIGHT\n");
			return RIGHT;
		}
		printf("\nLEFT\n");
		return LEFT;
	}
	
	else if (x<y){
		if (Stick->y_percent>0){
			printf("\nUP\n");
			return UP;
		}
		printf("\nDOWN\n");
		return DOWN;
	}
	
	else{
		printf("\nNEUTRAL\n");
		return NEUTRAL;
	}
}

void pos_calibrate(JoyStick *Stick){
	xmem_write(1, 0x400);
	_delay_us(15);
	Stick->x_neutralPoint = xmem_read(0x400);
	Stick->y_neutralPoint = xmem_read(0x400);
}

uint8_t joyStickClick(){
	if ((PIND & (1 << PD4)) == 0) {
		printf("THE BUTTON IS PRESSED");
		return 1;
	}
	return 0;
}