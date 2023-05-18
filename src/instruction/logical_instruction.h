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

// LHLD a    00101010 lb hb - Load H:L from memory
bool lhld(int machine_cycle, uint16_t* temporary_address);

// SHLD a    00100010 lb hb - Store H:L to memory
bool shld(int machine_cycle, uint16_t* temporary_address);

// LDAX RP   00RP1010 *1 - Load indirect through BC or DE
bool ldax(Register_Pair indirect_pair, int machine_cycle, uint16_t* temporary_address);

// STAX RP   00RP0010 *1 - Store indirect through BC or DE
bool stax(Register_Pair indirect_pair, int machine_cycle, uint16_t* temporary_address);

// XCHG      11101011 - Exchange DE and HL content
bool xchg();

#endif //_LOGICAL_INSTRUCTION_H_