
#pragma once

#include <stdint.h>
#include "motor_driver.h"
#include "SERVO_driver.h"
#include "solenoide.h"


#define CAN_BAUDRATE	0x00143156 //This gives bit time = 4 us
#define NUMBER_OF_TQ	16	//This gives TQ = 250 ns
#define TQ				250e-9 //250 ns
#define PROPAG			1	//2-1, mulig vi må endre denne til 1 men er litt usikker
#define PS1				6	//7-1
#define PS2				5	//6-1
#define SJW				3	//4-1


void can_init(uint8_t rxInterrupt);


// Strict-aliasing-safe reinterpret-cast
#define union_cast(type, x) \
    (((union { \
        typeof(x) a; \
        type b; \
    })x).b)


// Dummy type for use with `union_cast`, see below
typedef struct Byte8 Byte8;
struct Byte8 {
    uint8_t bytes[8];
};


typedef struct CanMsg CanMsg;
struct CanMsg {
    uint16_t id;
    uint8_t length;
    uint8_t data[8];    
};

// Send a CAN message on the bus. 
// Blocks if the bus does not receive the message (typically because one of the 
// receiving nodes has not cleared a buffer)
void can_tx(CanMsg m);

// Receive a CAN message.
// Does not block. Returns 0 if there is no message, 1 otherwise
uint8_t can_rx(CanMsg* m);

// Print a CAN message (using `printf`)
void can_printmsg(CanMsg m);





