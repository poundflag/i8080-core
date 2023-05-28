#include "cpu.h"
#include "memory/memory_controller.h"
#include "register/register_controller.h"
#include "instruction/instruction.h"

void run(int step) {
    for (int i = 0; i < step; i++) {
        // Read the current address
        uint8_t opcode = read(get_program_counter());

        // Decode & Execute
        decode_execute_instruction(opcode);
    }
}