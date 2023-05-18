#include <stdio.h>
#include "logical_instruction.h"
#include "../instruction/instruction.h"
#include "../memory/memory_controller.h"

void print_error_invalid_cycle(char* instruction_name) {
    fprintf(stderr, "Invalid machine cycle in logical instruction: %s\n", instruction_name);
}

bool mov(uint8_t* destination, uint8_t source_value) {
    *destination = source_value;
    return true;
}

bool mvi(uint8_t* destination, int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        *destination = read(get_program_counter());
        return true;
    default:
        print_error_invalid_cycle("MVI");
        break;
    }
    return false;
}

bool lxi(Register_Pair destination, int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        set_register_pair(destination, read(get_program_counter()) << 8);
        increment_program_counter();
        break;
    case 2:
        set_register_pair(destination,
            read(get_program_counter()) | get_register_pair(destination)
        );
        return true;
    default:
        print_error_invalid_cycle("LXI");
        break;
    }
    return false;
}

bool lda(int machine_cycle, uint16_t* temporary_address) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        *temporary_address = read(get_program_counter());
        break;
    case 1:
        increment_program_counter();
        *temporary_address |= read(get_program_counter()) << 8;
        break;
    case 2:
        uint16_t program_counter_value = get_program_counter();
        set_program_counter(*temporary_address);
        *temporary_address = program_counter_value;
        break;
    case 3:
        set_register(REG_A, read(get_program_counter()));
        set_program_counter(*temporary_address);
        return true;
    default:
        print_error_invalid_cycle("LDA");
        break;
    }
    return false;
}

bool sta(int machine_cycle, uint16_t* temporary_address) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        *temporary_address = read(get_program_counter());
        break;
    case 1:
        increment_program_counter();
        *temporary_address |= read(get_program_counter()) << 8;
        break;
    case 2:
        uint16_t program_counter_value = get_program_counter();
        set_program_counter(*temporary_address);
        *temporary_address = program_counter_value;
        break;
    case 3:
        write(get_program_counter(), get_register(REG_A));
        set_program_counter(*temporary_address);
        return true;
    default:
        print_error_invalid_cycle("STA");
        break;
    }
    return false;
}
