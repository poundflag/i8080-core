#include "instruction/logical_instruction.h"
#include "instruction/instruction.h"
#include "io/io_controller.h"
#include "memory/memory_controller.h"
#include "register/stack.h"
#include "status_service.h"
#include <stdio.h>

void print_error_invalid_cycle(char *instruction_name) { fprintf(stderr, "Invalid machine cycle in logical instruction: %s\n", instruction_name); }

void swap_program_counter_and_value(uint16_t *value) {
    uint16_t program_counter_value = get_program_counter();
    set_program_counter(*value);
    *value = program_counter_value;
}

// Reads a memory address and then sets the program counter to it
void read_memory_address(int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        *temporary_address = read_from_memory(get_program_counter());
        break;
    case 1:
        increment_program_counter();
        *temporary_address |= read_from_memory(get_program_counter()) << 8;
        break;
    case 2:
        swap_program_counter_and_value(temporary_address);
        break;
    default:
        fprintf(stderr, "Wrong machine cycle when reading memory address in "
                        "logical instruction\n");
        break;
    }
}

// Writes a memory address and then sets the program counter to it
void write_memory_address(int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        *temporary_address = read_from_memory(get_program_counter());
        break;
    case 1:
        increment_program_counter();
        *temporary_address |= read_from_memory(get_program_counter()) << 8;
        break;
    case 2:
        swap_program_counter_and_value(temporary_address);
        break;
    default:
        fprintf(stderr, "Wrong machine cycle when writing memory address in "
                        "logical instruction\n");
        break;
    }
}

bool mov(Register destination, Register source) {
    set_register(destination, get_register(source));
    return true;
}

bool mvi(Register destination, int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        set_register(destination, read_from_memory(get_program_counter()));
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
        set_register_pair(destination, read_from_memory(get_program_counter()));
        increment_program_counter();
        break;
    case 2:
        set_register_pair(destination, (read_from_memory(get_program_counter()) << 8) | get_register_pair(destination));
        return true;
    default:
        print_error_invalid_cycle("LXI");
        break;
    }
    return false;
}

bool lda(int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
    case 1:
    case 2:
        read_memory_address(machine_cycle, temporary_address);
        break;
    case 3:
        set_register(REG_A, read_from_memory(get_program_counter()));
        swap_program_counter_and_value(temporary_address);
        return true;
    default:
        print_error_invalid_cycle("LDA");
        break;
    }
    return false;
}

bool sta(int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
    case 1:
        write_memory_address(machine_cycle, temporary_address);
        break;
    case 2:
        set_memory_read(false);
        set_write_output(true);
        write_memory_address(machine_cycle, temporary_address);
        break;
    case 3:
        set_memory_read(true);
        set_write_output(false);
        write_to_memory(get_program_counter(), get_register(REG_A));
        swap_program_counter_and_value(temporary_address);
        return true;
    default:
        print_error_invalid_cycle("STA");
        break;
    }
    return false;
}

bool lhld(int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
    case 1:
    case 2:
        read_memory_address(machine_cycle, temporary_address);
        break;
    case 3:
        set_register(REG_L, read_from_memory(get_program_counter()));
        increment_program_counter();
        break;
    case 4:
        set_register(REG_H, read_from_memory(get_program_counter()));
        swap_program_counter_and_value(temporary_address);
        return true;
    default:
        print_error_invalid_cycle("LHLD");
        break;
    }
    return false;
}

bool shld(int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
    case 1:
        write_memory_address(machine_cycle, temporary_address);
        break;
    case 2:
        set_memory_read(false);
        set_write_output(true);
        write_memory_address(machine_cycle, temporary_address);
        break;
    case 3:
        write_to_memory(get_program_counter(), get_register(REG_L));
        increment_program_counter();
        break;
    case 4:
        set_memory_read(true);
        set_write_output(false);
        write_to_memory(get_program_counter(), get_register(REG_H));
        swap_program_counter_and_value(temporary_address);
        return true;
    default:
        print_error_invalid_cycle("SHLD");
        break;
    }
    return false;
}

bool ldax(Register_Pair indirect_pair, int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
        *temporary_address = get_register_pair(indirect_pair);
        swap_program_counter_and_value(temporary_address);
        break;
    case 1:
        set_register(REG_A, read_from_memory(get_program_counter()));
        swap_program_counter_and_value(temporary_address);
        return true;
    default:
        print_error_invalid_cycle("LDAX");
        break;
    }
    return false;
}

bool stax(Register_Pair indirect_pair, int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
        set_memory_read(false);
        set_write_output(true);
        *temporary_address = get_register_pair(indirect_pair);
        swap_program_counter_and_value(temporary_address);
        break;
    case 1:
        set_memory_read(true);
        set_write_output(false);
        write_to_memory(get_program_counter(), get_register(REG_A));
        swap_program_counter_and_value(temporary_address);
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

bool rst(int number) {
    push_word(get_program_counter() + 1);
    set_program_counter((number * 8) - 1);
    return true;
}

bool push(Register_Pair register_pair, int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
        set_stack_access(true);
        set_memory_read(false);
        set_write_output(true);
        *temporary_address = get_program_counter();
        set_program_counter(get_stack_pointer() - 1);
        break;
    case 1:
        set_program_counter(get_program_counter() - 1);
        break;
    case 2:
        set_stack_access(false);
        set_memory_read(true);
        set_write_output(false);
        set_program_counter(*temporary_address);
        push_word(get_register_pair(register_pair));
        return true;
    default:
        break;
    }
    return false;
}

bool pop(Register_Pair register_pair, int machine_cycle, uint16_t *temporary_address) {
    switch (machine_cycle) {
    case 0:
        set_stack_access(true);
        *temporary_address = get_program_counter();
        set_program_counter(get_stack_pointer() - 1);
        break;
    case 1:
        set_program_counter(get_program_counter() - 1);
        break;
    case 2:
        set_stack_access(false);
        set_program_counter(*temporary_address);
        set_register_pair(register_pair, pull_word());
        return true;
    default:
        break;
    }
    return false;
}

bool xthl() {
    uint16_t temporary_value = get_register_pair(PAIR_H);
    set_register_pair(PAIR_H, pull_word());
    push_word(temporary_value);
    return true;
}

bool sphl() {
    set_stack_pointer(get_register_pair(PAIR_H));
    return true;
}

bool in(uint8_t machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        set_device_input(true);
        set_register(REG_A, read_port(read_from_memory(get_program_counter())));
        break;
    case 2:
        set_device_input(false);
        return true;
    default:
        break;
    }
    return false;
}

bool out(uint8_t machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        set_device_output(true);
        set_write_output(true);
        write_port(read_from_memory(get_program_counter()), get_register(REG_A));
        break;
    case 2:
        set_device_output(false);
        set_write_output(false);
        return true;
    default:
        break;
    }
    return false;
}

bool hlt() {
    set_system_halt(true);
    return true;
}
