#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "register_controller.h"

#ifndef _FLAG_REGISTER_H_
#define _FLAG_REGISTER_H_

typedef enum {
    CARRY = 0,
    PARITY = 2,
    AUXILIARY = 4,
    ZERO = 6,
    SIGNED = 7
} Flag_Type;

typedef enum {
    PLUS_OPERATION,
    SUBTRACTION_OPERATION
} Arithmetic_Operation;

bool is_result_zero(uint8_t result);
bool is_result_signed(uint8_t result);
bool is_result_parity(uint8_t result);
bool is_result_carry(uint16_t result);
bool is_result_auxiliary_carry(uint8_t value_one, uint8_t value_two, Arithmetic_Operation operator);
uint8_t process_flag_register(uint8_t value_one, uint8_t value_two, Arithmetic_Operation operator);
bool get_flag_status(Flag_Type flag);
void set_flag_status(Flag_Type flag, bool state);

#endif //_FLAG_REGISTER_H_