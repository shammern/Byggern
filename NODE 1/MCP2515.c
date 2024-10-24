/*
 * MCP2515.c
 *
 * Created: 10.10.2024 09:55:07
 *  Author: danienes
 */ 

#include "MCP2515.h"

void mcp2515_reset(){
	SPI_slaveSelect();
	SPI_write(MCP_RESET);	
	SPI_slaveDeselect();
	_delay_ms(5);
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result ;
	SPI_slaveSelect();// Select CAN - controller
	SPI_write(MCP_READ); // Send read instruction
	SPI_write(address); // Send address to read from
	result = SPI_receive(); // Read result
	SPI_slaveDeselect(); // Deselect CAN - controller
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data){
	SPI_slaveSelect();
	SPI_write(MCP_WRITE);
	SPI_write(address);
	SPI_write(data);
	SPI_slaveDeselect();
}

void mcp2515_init(){
	SPI_init(); // Initialize SPI
	mcp2515_reset(); // Send reset - command
	
	_delay_ms(2);
	
	// Self - test
	uint8_t value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf(" MCP2515 is NOT in configuration mode after reset !\n");
	}
	
	uint8_t BRP = F_CPU_CAN/(2*NUMBER_OF_TQ*BAUDRATE); //Finner baudrateprescaler
	
	mcp2515_write(MCP_CNF1, SJW4 | (BRP-1));
	mcp2515_write(MCP_CNF2, BTLMODE | SAMPLE_3X | ((PS1-1) << 3) | (PROPAG - 1));
	mcp2515_write(MCP_CNF3, WAKFIL_DISABLE | (PS2-1));
}


void mcp2515_request_to_send(){
	SPI_slaveSelect();
	SPI_write(MCP_RTS_TX0); //Sjekker om TX0 registeret har data som skal sendes og setter interrupt flag
	SPI_slaveDeselect();
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	SPI_slaveSelect();
	SPI_write(MCP_BITMOD);
	SPI_write(address);
	SPI_write(mask);
	SPI_write(data);
	SPI_slaveDeselect();
}

uint8_t mcp2515_read_status(){
	uint8_t status;
	SPI_slaveSelect();
	SPI_write(MCP_READ_STATUS);
	status = SPI_receive();
	SPI_slaveDeselect();
	return status;
}

uint8_t mcp2515_set_mode(uint8_t mode){
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, mode);
	
	uint8_t current_mode = mcp2515_read(MCP_CANSTAT);
	if((current_mode & MODE_MASK) != mode){
		printf("ERROR: NOT IN CORRECT OPERATIONALMODE");
		return 1;
	}	
	return 0;
}
