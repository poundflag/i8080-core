#include "instruction.h"
#include "logical_instruction.h"

void decode_execute_instruction(uint8_t opcode) {
    if (opcode >= 0x40 && opcode <= 0x7F && opcode != 0x76) {
        mov(0, 0);
    }
}

uint8_t getDestinationIndex(uint8_t opcode) {
    return 0;
}

uint8_t getSourceIndex(uint8_t opcode) {
    return 0;
}
