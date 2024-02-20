#include "register/stack.h"
#include "memory/memory_controller.h"

uint16_t stack_pointer = 0;

uint16_t get_stack_pointer() { return stack_pointer; }

void set_stack_pointer(uint16_t stack_pointer_address) { stack_pointer = stack_pointer_address; }

void push_word(uint16_t word_value) {
    set_stack_pointer((get_stack_pointer() - 2) & 0xFFFF);

    uint8_t low_byte = word_value & 0xFF;
    uint8_t high_byte = word_value >> 8;

    write_to_memory(get_stack_pointer(), low_byte);
    write_to_memory(get_stack_pointer() + 1, high_byte);
}

uint16_t pull_word() {
    set_stack_pointer((get_stack_pointer() + 2) & 0xFFFF);

    uint8_t low_byte = read_from_memory(get_stack_pointer() - 2);
    uint8_t high_byte = read_from_memory(get_stack_pointer() - 1);

    return low_byte | (high_byte << 8);
}
