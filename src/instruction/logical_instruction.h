#include <stdint.h>

#ifndef _LOGICAL_INSTRUCTION_H_
#define _LOGICAL_INSTRUCTION_H_

// MOV D,S   01DDDSSS - Move register to register
void mov(uint8_t* destination, uint8_t source);

// MVI D,#   00DDD110 db - Move immediate to register
void mvi(uint8_t* destination);

// LXI RP,#  00RP0001 lb hb - Load register pair immediate
void lxi();

#endif //_LOGICAL_INSTRUCTION_H_