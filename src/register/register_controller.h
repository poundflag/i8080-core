#include <stdint.h>

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
    REG_ENUM_SIZE
} Register;

typedef enum {
    PAIR_PSW,
    PAIR_B,
    PAIR_D,
    PAIR_H,
    PAIR_ENUM_SIZE
} Register_Pair;

uint8_t get_register(Register source);
void set_register(Register source, uint8_t value);
uint16_t get_register_pair(Register_Pair source);
void set_register_pair(Register_Pair source, uint16_t value);
uint16_t get_program_counter();
void set_program_counter(uint16_t value);
void increment_program_counter();

#endif //_REGISTER_CONTROLLER_H_