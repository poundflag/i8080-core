#include "logical_instruction.h"
#include "../instruction/instruction.h"
#include "../register/register_controller.h"
#include "../memory/memory_controller.h"

void mov(uint8_t* destination, uint8_t source) {
    *destination = source;
}

void mvi(uint8_t* destination) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        *destination = read(get_program_counter());
        break;
    default:
        reset_machine_cycle();
        break;
    }
}
