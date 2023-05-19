#include <stdio.h>
#include "arithmetic_instruction.h"
#include "../memory/memory_controller.h"

void set_flag_register(uint8_t value_one, uint8_t value_two, bool carry) {
    int parity_table[256] = {
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

uint8_t alu_add(uint8_t value_one, uint8_t value_two, bool carry_bit) {
    set_flag_register(value_one, value_two, carry_bit);
    return value_one + value_two + carry_bit;
}

uint8_t alu_sub(uint8_t value_one, uint8_t value_two, bool carry_bit) {
    uint8_t result = alu_add(value_one, (~value_two + !carry_bit) - carry_bit, carry_bit);
    bool carry = get_register(REG_F) & 1;
    set_register(REG_F, ((get_register(REG_F) >> 1) << 1) | !carry);
    return result;
}

bool add(Register source) {
    uint8_t result = alu_add(get_register(REG_A), get_register(source), false);
    set_register(REG_A, result);
    return true;
}

bool adi(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = alu_add(get_register(REG_A), read(get_program_counter()), false);
        set_register(REG_A, result);
        return true;
    }
    return false;
}

bool adc(Register source, bool carry_bit) {
    uint8_t result = alu_add(get_register(REG_A), get_register(source), carry_bit);
    set_register(REG_A, result);
    return true;
}

bool aci(bool carry_bit, int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = alu_add(get_register(REG_A), read(get_program_counter()), carry_bit);
        set_register(REG_A, result);
        return true;
    }
    return false;
}

bool sub(Register source) {
    uint8_t result = alu_sub(get_register(REG_A), get_register(source), false);
    set_register(REG_A, result);
    return true;
}

bool sui(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = alu_sub(get_register(REG_A), read(get_program_counter()), false);
        set_register(REG_A, result);
        return true;
    }
    return false;
}

bool sbb(Register source, bool carry_bit) {
    uint8_t result = alu_sub(get_register(REG_A), get_register(source), carry_bit);
    set_register(REG_A, result);
    return true;
}

bool sbi(bool carry_bit, int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = alu_sub(get_register(REG_A), read(get_program_counter()), carry_bit);
        set_register(REG_A, result);
        return true;
    }
    return false;
}

bool inr(Register source) {
    bool carry = get_register(REG_F) & 1;
    uint8_t result = alu_add(get_register(source), 1, false);
    set_register(source, result);
    set_register(REG_F, ((get_register(REG_F) >> 1) << 1) | carry);
    return true;
}

bool dcr(Register source) {
    bool carry = get_register(REG_F) & 1;
    uint8_t result = alu_sub(get_register(source), 1, false);
    set_register(source, result);
    set_register(REG_F, ((get_register(REG_F) >> 1) << 1) | carry);
    return true;
}

bool inx(Register_Pair source) {
    set_register_pair(source, get_register_pair(source) + 1);
    return true;
}

bool dcx(Register_Pair source) {
    set_register_pair(source, get_register_pair(source) - 1);
    return true;
}
