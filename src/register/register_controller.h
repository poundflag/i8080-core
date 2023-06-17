#include <stdint.h>
#include <stdbool.h>

#ifndef _REGISTER_CONTROLLER_H_
#define _REGISTER_CONTROLLER_H_

typedef enum {
    REG_A,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    REG_F,
    REG_ENUM_SIZE,
    REG_M
} Register;

typedef enum {
    PAIR_PSW,
    PAIR_B,
    PAIR_D,
    PAIR_H,
    PAIR_ENUM_SIZE,
    PAIR_SP
} Register_Pair;

typedef enum {
    CARRY = 0,
    PARITY = 2,
    AUXILIARY = 4,
    ZERO = 6,
    SIGNED = 7
} Flag_Type;

uint8_t get_register(Register destination);
void set_register(Register destination, uint8_t value);
uint16_t get_register_pair(Register_Pair destination);
void set_register_pair(Register_Pair destination, uint16_t value);
uint16_t get_program_counter();
void set_program_counter(uint16_t value);
void increment_program_counter();
bool get_register_bit(Register register_source, int bit_index);
void set_register_bit(Register register_source, int bit_index, bool state);

#endif //_REGISTER_CONTROLLER_H_