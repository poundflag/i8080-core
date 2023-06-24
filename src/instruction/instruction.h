#include "../register/register_controller.h"
#include <stdint.h>

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

bool decode_execute_instruction(uint8_t opcode, int machine_cycle,
                                uint16_t *temporary_address);
Register get_destination_register(uint8_t opcode);
Register get_source_register(uint8_t opcode);

#endif //_INSTRUCTION_H_