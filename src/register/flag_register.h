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

uint8_t process_flag_register(uint8_t value_one, uint8_t value_two, bool carry, char operator);
bool check_flag_statement(Flag_Type flag, uint8_t value_one, uint8_t value_two, bool carry, char operator);
bool get_flag_status(Flag_Type flag);
void set_flag_status(Flag_Type flag, bool state);

#endif //_FLAG_REGISTER_H_