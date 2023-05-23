#include "register_controller.h"

uint8_t register_array[REG_ENUM_SIZE] = { 
    [REG_F] = 0b00000010
 };

struct Register_Pair_Struct {
    Register low;
    Register high;
};

struct Register_Pair_Struct register_pair_array[PAIR_ENUM_SIZE] = {
    {.low = REG_A, .high = REG_F},
    {.low = REG_B, .high = REG_C},
    {.low = REG_D, .high = REG_E},
    {.low = REG_H, .high = REG_L}
};

uint16_t program_counter = 0;

uint8_t get_register(Register source) {
    return register_array[source];
}

void set_register(Register source, uint8_t value) {
    register_array[source] = value;
}

uint16_t get_register_pair(Register_Pair source) {
    return register_array[register_pair_array[source].low] | (register_array[register_pair_array[source].high] << 8);
}

void set_register_pair(Register_Pair source, uint16_t value) {
    register_array[register_pair_array[source].low] = value & 0xFF;
    register_array[register_pair_array[source].high] = (value >> 8) & 0xFF;
}

uint16_t get_program_counter() {
    return program_counter;
}

void set_program_counter(uint16_t value) {
    program_counter = value;
}

void increment_program_counter() {
    program_counter++;
}


bool get_register_bit(Register register_source, int bit_index) {
    return (get_register(register_source) >> bit_index) & 1;
}

void set_register_bit(Register register_source, int bit_index, bool state) {
    uint8_t temporary_register_value = get_register(register_source);
    if (state) {
        temporary_register_value |= (1 << bit_index);
    }
    else {
        temporary_register_value &= ~(1 << bit_index);
    }
    set_register(register_source, temporary_register_value);
}