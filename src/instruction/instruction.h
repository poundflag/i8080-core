#include <stdint.h>

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

void reset_machine_cycle();
void decode_execute_instruction(uint8_t opcode);
uint8_t getDestinationIndex(uint8_t opcode);
uint8_t getSourceIndex(uint8_t opcode);

#endif //_INSTRUCTION_H_