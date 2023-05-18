#include <stdint.h>
#include <stdbool.h>
#include "../register/register_controller.h"

#ifndef _LOGICAL_INSTRUCTION_H_
#define _LOGICAL_INSTRUCTION_H_

// MOV D,S   01DDDSSS - Move register to register
bool mov(uint8_t* destination, uint8_t source_value);

// MVI D,#   00DDD110 db - Move immediate to register
bool mvi(uint8_t* destination, int machine_cycle);

// LXI RP,#  00RP0001 lb hb - Load register pair immediate
bool lxi(Register_Pair destination, int machine_cycle);

// LDA a     00111010 lb hb - Load A from memory
bool lda(int machine_cycle, uint16_t* temporary_address);

// STA a     00110010 lb hb - Store A to memory
bool sta(int machine_cycle, uint16_t* temporary_address);

#endif //_LOGICAL_INSTRUCTION_H_