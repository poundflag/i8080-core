#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "register_controller.h"

#ifndef _FLAG_REGISTER_H_
#define _FLAG_REGISTER_H_

typedef enum {
    CARRY,
    PARITY,
    AUXILIARY,
    ZERO,
    SIGNED
} Flag_Type;

void process_flag_register(uint8_t value_one, uint8_t value_two, bool carry);
bool check_flag_statement(Flag_Type flag, uint8_t value_one, uint8_t value_two, bool carry);
bool get_flag_status(Flag_Type flag);
bool set_flag_status(Flag_Type flag, bool value);

#endif //_FLAG_REGISTER_H_