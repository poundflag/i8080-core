#include <stdint.h>
#include <stdbool.h>
#include "../register/register_controller.h"

#ifndef _LOGICAL_INSTRUCTION_H_
#define _LOGICAL_INSTRUCTION_H_

void decode_execute_logical_instructions(uint8_t opcode);

// MOV D,S   01DDDSSS - Move register to register
bool mov(Register destination, Register source);

// MVI D,#   00DDD110 db - Move immediate to register
bool mvi(Register destination, int machine_cycle);

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

// RST n     11NNN111          -       Restart (Call n*8)
bool rst(int number);

// PUSH RP   11RP0101 *2       -       Push register pair on the stack
bool push(int machine_cycle, uint16_t* temporary_address, Register_Pair register_pair);

// POP RP    11RP0001 *2       *2      Pop  register pair from the stack
bool pop(int machine_cycle, uint16_t* temporary_address, Register_Pair register_pair);

// XTHL      11100011          -       Swap H:L with top word on stack
bool xthl();

// SPHL      11111001          -       Set SP to content of H:L
bool sphl();

// IN p      11011011 pa       -       Read input port into A
bool in(int port_number);

// OUT p     11010011 pa       -       Write A to output port
bool out(int port_number);

// HLT       01110110          -       Halt processor
bool hlt();

#endif //_LOGICAL_INSTRUCTION_H_