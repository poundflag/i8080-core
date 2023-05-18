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

bool lhld(int machine_cycle, uint16_t* temporary_address) {
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
        set_register(REG_L, read(get_program_counter()));
        increment_program_counter();
        break;
    case 4:
        set_register(REG_H, read(get_program_counter()));
        set_program_counter(*temporary_address);
        return true;
    default:
        print_error_invalid_cycle("LHLD");
        break;
    }
    return false;
}

bool shld(int machine_cycle, uint16_t* temporary_address) {
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
        write(get_program_counter(), get_register(REG_L));
        increment_program_counter();
        break;
    case 4:
        write(get_program_counter(), get_register(REG_H));
        set_program_counter(*temporary_address);
        return true;
    default:
        print_error_invalid_cycle("SHLD");
        break;
    }
    return false;
}

bool ldax(Register_Pair indirect_pair, int machine_cycle, uint16_t* temporary_address) {
    switch (machine_cycle) {
    case 0:
        uint16_t program_counter_value = get_program_counter();
        set_program_counter(get_register_pair(indirect_pair));
        *temporary_address = program_counter_value;
        break;
    case 1:
        set_register(REG_A, read(get_program_counter()));
        set_program_counter(*temporary_address);
        return true;
    default:
        print_error_invalid_cycle("LDAX");
        break;
    }
    return false;
}

bool stax(Register_Pair indirect_pair, int machine_cycle, uint16_t* temporary_address) {
    switch (machine_cycle) {
    case 0:
        uint16_t program_counter_value = get_program_counter();
        set_program_counter(get_register_pair(indirect_pair));
        *temporary_address = program_counter_value;
        break;
    case 1:
        write(get_program_counter(), get_register(REG_A));
        set_program_counter(*temporary_address);
        return true;
    default:
        print_error_invalid_cycle("STAX");
        break;
    }
    return false;
}

bool xchg() {
    uint16_t temp_value = get_register_pair(PAIR_D);
    set_register_pair(PAIR_D, get_register_pair(PAIR_H));
    set_register_pair(PAIR_H, temp_value);
    return true;
}
