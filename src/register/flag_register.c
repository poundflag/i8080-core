#include "flag_register.h"
#include "register_controller.h"

static const int parity_table[256] = {
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1,
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1,
          1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1,
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
          0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1,
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
          1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1 };

bool is_result_zero(uint8_t result) {
    return result == 0;
}

bool is_result_signed(uint8_t result) {
    return (result & 0x80) == 0x80;
}

bool is_result_parity(uint8_t result) {
    return parity_table[result & 0xFF];
}

bool is_result_carry(uint16_t result) {
    return (result & 0x100) == 0x100;
}

bool is_result_auxiliary_carry(uint8_t value_one, uint8_t value_two, Arithmetic_Operation operator) {
    if (operator == PLUS_OPERATION) {
        return ((value_one & 0xF) + (value_two & 0xF)) > 0xF;
    }
    else {
        bool carry_result = is_result_carry(value_one - value_two);
        value_two = (~value_two) & 0xFF;
        uint16_t result = value_one + value_two + (1 - carry_result);
        uint16_t new_carry = result ^ value_one ^ value_two;
        return (new_carry & 0x10) != 0;
    }
}

uint8_t process_flag_register(uint8_t value_one, uint8_t value_two, Arithmetic_Operation operator) {
    uint16_t result = 0;
    if (operator == PLUS_OPERATION) {
        result = value_one + value_two;
    }
    else {
        result = value_one - value_two;
    }

    bool carry_bit = is_result_carry(result);
    bool parity_bit = is_result_parity(result & 0xFF);
    bool auxiliary_bit = is_result_auxiliary_carry(value_one, value_two, operator);
    bool zero_bit = is_result_zero(result & 0xFF);
    bool signed_bit = is_result_signed(result & 0xFF);

    return carry_bit | 2 | (parity_bit << 2) | (auxiliary_bit << 4) | (zero_bit << 6) | (signed_bit << 7);
}
