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

uint8_t process_flag_register(uint8_t value_one, uint8_t value_two, bool carry, char operator) {

    bool zero_bit = check_flag_statement(ZERO, value_one, value_two, carry, operator);
    bool signed_bit = check_flag_statement(SIGNED, value_one, value_two, carry, operator);
    bool parity_bit = check_flag_statement(PARITY, value_one, value_two, carry, operator);
    bool carry_bit = check_flag_statement(CARRY, value_one, value_two, carry, operator);
    set_flag_status(CARRY, carry_bit);
    bool auxiliary_bit = check_flag_statement(AUXILIARY, value_one, value_two, carry_bit, operator);

    printf("Carry %d\n", carry_bit);
    printf("Parity %d\n", parity_bit);
    printf("Auxiliary %d\n", auxiliary_bit);
    printf("Zero Bit %d\n", zero_bit);
    printf("Signed %d\n", signed_bit);

    return carry_bit | 2 | (parity_bit << 2) | (auxiliary_bit << 4) | (zero_bit << 6) | (signed_bit << 7);
}

bool check_flag_statement(Flag_Type flag, uint8_t value_one, uint8_t value_two, bool carry, char operator) {
    uint16_t result = 0;
    if (operator == '+') {
        result = value_one + value_two + carry;
    }
    else {
        result = value_one - value_two;
    }

    switch (flag) {
    case CARRY:
        return (result & 0x100) == 0x100;
    case PARITY:
        return parity_table[result & 0xFF];
    case AUXILIARY:
        if (operator == '+') {
            return ((value_one & 0xF) + (value_two & 0xF)) > 0xF;
        }
        else {
            /*
            value2 = ~value2;
            uint16_t result = value1 + value2 + (1 - getFlag(FlagRegister::Carry));
            uint16_t newCarry = result ^ value1 ^ value2;
            setFlag(Flag::AuxiliaryCarry, (newCarry & (1 << 4)) != 0);
            */
            value_two = (~value_two) & 0xFF;
            result = (value_one & 0xFF) + value_two + (1-carry);
            uint16_t new_carry = result ^ (value_one & 0xFF) ^ value_two;
            printf("Value 1 %d\n", value_one);
            printf("Value 2 %d\n", value_two);
            return (new_carry & (1 << 4)) != 0;
        }
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
    return (get_register(REG_F) >> flag) & 1;
}

void set_flag_status(Flag_Type flag, bool state) {
    uint8_t flag_register_value = get_register(REG_F);
    if (state) {
        flag_register_value |= (1 << flag);
    }
    else {
        flag_register_value &= ~(1 << flag);
    }
    set_register(REG_F, flag_register_value);
}
