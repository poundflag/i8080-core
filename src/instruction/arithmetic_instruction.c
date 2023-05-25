#include <stdio.h>
#include "arithmetic_instruction.h"
#include "../memory/memory_controller.h"
#include "../register/flag_register.h"

uint8_t alu_add(uint8_t value_one, uint8_t value_two, bool carry_bit) {
    set_register(REG_F, process_flag_register(value_one, value_two + carry_bit, PLUS_OPERATION));
    return value_one + value_two + carry_bit;
}

uint8_t alu_sub(uint8_t value_one, uint8_t value_two, bool carry_bit) {
    set_register(REG_F, process_flag_register(value_one, value_two - carry_bit, SUBTRACTION_OPERATION));
    return value_one - value_two - carry_bit;
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
    bool carry = get_register_bit(REG_F, CARRY);
    uint8_t result = alu_add(get_register(source), 1, false);
    set_register(source, result);
    set_register_bit(REG_F, CARRY, carry);
    return true;
}

bool dcr(Register source) {
    bool carry = get_register_bit(REG_F, CARRY);
    uint8_t result = alu_sub(get_register(source), 1, false);
    set_register(source, result);
    set_register_bit(REG_F, CARRY, carry);
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

bool dad(Register_Pair source) {
    uint16_t h_value = get_register_pair(PAIR_H);
    uint16_t source_value = get_register_pair(source);
    set_register_pair(PAIR_H, (h_value + source_value) & 0xFFFF);
    bool carry = (h_value + source_value) > 0xFFFF;
    set_register_bit(REG_F, CARRY, carry);
    return true;
}

bool daa() {
    // Stolen from
    // https://github.com/GunshipPenguin/lib8080/blob/master/src/i8080.c
    // Line: 405 | I don't really know, what this mess does
    uint8_t a_value = get_register(REG_A);
    uint8_t temp_value = 0;

    // If the least significant four bits of the accumulator represents a number
    // greater than 9, or if the Auxiliary Carry bit is equal to one, the
    // accumulator is incremented by six. Otherwise, no incrementing occurs.
    if (((a_value & 0xF) > 9) || (get_register(REG_F) >> 4) == 1) {
        temp_value += 0x06;
    }

    bool carry = get_register(REG_F) & 1;

    // If the most significant four bits of the accumulator now represent a number
    // greater than 9, or if the normal carry bit is equal to one, the most
    // significant four bits of the accumulator are incremented by six.
    if (((a_value & 0xF0) > 0x90) ||
        (((a_value & 0xF0) >= 0x90) && ((a_value & 0xF) > 9)) ||
        (carry == 1)) {
        temp_value |= 0x60;
        carry = true;
    }
    alu_add(a_value, temp_value, false);
    // TODO Add Carry
    set_register(REG_A, a_value + temp_value);
    return true;
}

bool ana(Register source) {
    uint8_t result = get_register(REG_A) & get_register(source);
    set_register(REG_A, result);
    return true;
}

bool ani(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = get_register(REG_A) & read(get_program_counter());
        set_register(REG_A, result);
        return true;
    }
    return false;
}

bool ora(Register source) {
    uint8_t result = get_register(REG_A) | get_register(source);
    set_register(REG_A, result);
    return true;
}

bool ori(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = get_register(REG_A) | read(get_program_counter());
        set_register(REG_A, result);
        return true;
    }
    return false;
}

bool xra(Register source) {
    uint8_t result = get_register(REG_A) ^ get_register(source);
    set_register(REG_A, result);
    return true;
}

bool xri(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = get_register(REG_A) ^ read(get_program_counter());
        set_register(REG_A, result);
        return true;
    }
    return false;
}

bool cmp(Register source) {
    alu_sub(get_register(REG_A), get_register(source), false);
    return true;
}

bool cpi(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        alu_sub(get_register(REG_A), read(get_program_counter()), false);
        return true;
    }
    return false;
}

bool rlc() {
    uint8_t a_value = get_register(REG_A);
    bool last_bit_of_value = (a_value >> 7) & 1;
    set_register(REG_A, (a_value << 1 | last_bit_of_value) & 0xFF);
    set_register_bit(REG_F, CARRY, (a_value & 0x80) == 0x80);
    return true;
}

bool rrc() {
    uint8_t a_value = get_register(REG_A);
    uint8_t first_bit_of_value = (a_value << 7) & 0x80;
    set_register(REG_A, (a_value >> 1 | first_bit_of_value) & 0xFF);
    set_register_bit(REG_F, CARRY, (a_value & 1) == 1);
    return true;
}

bool ral() {
    uint8_t a_value = get_register(REG_A);
    bool carry_value = get_register_bit(REG_F, CARRY);
    set_register(REG_A, (a_value << 1 | carry_value) & 0xFF);
    set_register_bit(REG_F, CARRY, (a_value & 0x80) == 0x80);
    return true;
}

bool rar() {
    uint8_t a_value = get_register(REG_A);
    uint8_t carry_value = (get_register_bit(REG_F, CARRY) << 7) & 0x80;
    set_register(REG_A, (a_value >> 1 | carry_value) & 0xFF);
    set_register_bit(REG_F, CARRY, (a_value & 1) == 1);
    return true;
}

bool cma() {
    set_register(REG_A, ~get_register(REG_A));
    return true;
}

bool cmc() {
    set_register_bit(REG_F, CARRY, !get_register_bit(REG_F, CARRY));
    return true;
}

bool stc() {
    set_register_bit(REG_F, CARRY, true);
    return true;
}
