#include "register_controller.h"

uint8_t register_array[REG_ENUM_SIZE] = { 0 };

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
