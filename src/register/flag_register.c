#include "flag_register.h"

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

void set_flag_register1(uint8_t value_one, uint8_t value_two, bool carry) {


    uint16_t result = value_one + value_two + carry;

    bool zero_bit = (result & 0xFF) == 0;
    bool signed_bit = (result & 0x80) == 0x80;
    bool parity_bit = parity_table[result & 0xFF];
    bool carry_bit = (result & 0x100) == 0x100;
    bool auxiliary_bit = ((value_one & 0x0F) + (value_two & 0x0F) + carry) > 0x0F;

    /*printf("Carry %d\n", carry_bit);
    printf("Parity %d\n", parity_bit);
    printf("Auxiliary %d\n", auxiliary_bit);
    printf("Zero Bit %d\n", zero_bit);
    printf("Signed %d\n", signed_bit);
    printf("Result %d\n\n", result);*/

    set_register(REG_F, carry_bit | 2 | (parity_bit << 2) | (auxiliary_bit << 4) | (zero_bit << 6) | (signed_bit << 7));
}

bool check_flag_statement(Flag_Type flag, uint8_t value_one, uint8_t value_two, bool carry) {
    uint16_t result = value_one + value_two + carry;

    switch (flag) {
    case CARRY:
        return (result & 0x100) == 0x100;
    case PARITY:
        return parity_table[result & 0xFF];
    case AUXILIARY:
        return ((value_one & 0x0F) + (value_two & 0x0F) + carry) > 0x0F;
    case ZERO:
        return (result & 0xFF) == 0;
    case SIGNED:
        return (result & 0x80) == 0x80;
    default:
        fprintf(stderr, "Wrong flag enum in check_flag_statement");
    }
    return false;
}

bool get_flag_status(Flag_Type flag) {
    return false;
}
