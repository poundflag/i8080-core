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

uint8_t alu_and(uint8_t value_one, uint8_t value_two) {
    set_register(REG_F, process_flag_register(value_one & value_two, 0, PLUS_OPERATION));
    return value_one & value_two;
}

uint8_t alu_or(uint8_t value_one, uint8_t value_two) {
    set_register(REG_F, process_flag_register(value_one | value_two, 0, PLUS_OPERATION));
    return value_one | value_two;
}

uint8_t alu_xor(uint8_t value_one, uint8_t value_two) {
    set_register(REG_F, process_flag_register(value_one ^ value_two, 0, PLUS_OPERATION));
    return value_one ^ value_two;
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

bool adc(Register source) {
    uint8_t result = alu_add(get_register(REG_A), get_register(source), get_register_bit(REG_F, CARRY));
    set_register(REG_A, result);
    return true;
}

bool aci(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = alu_add(get_register(REG_A), read(get_program_counter()), get_register_bit(REG_F, CARRY));
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

bool sbb(Register source) {
    uint8_t result = alu_sub(get_register(REG_A), get_register(source), get_register_bit(REG_F, CARRY));
    set_register(REG_A, result);
    return true;
}

bool sbi(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        uint8_t result = alu_sub(get_register(REG_A), read(get_program_counter()), get_register_bit(REG_F, CARRY));
        set_register(REG_A, result);
        return true;
    }
    return false;
}

bool inr(Register destination) {
    bool carry = get_register_bit(REG_F, CARRY);
    uint8_t result = alu_add(get_register(destination), 1, false);
    set_register(destination, result);
    set_register_bit(REG_F, CARRY, carry);
    return true;
}

bool dcr(Register destination) {
    bool carry = get_register_bit(REG_F, CARRY);
    uint8_t result = alu_sub(get_register(destination), 1, false);
    set_register(destination, result);
    set_register_bit(REG_F, CARRY, carry);
    return true;
}

bool inx(Register_Pair destination) {
    set_register_pair(destination, get_register_pair(destination) + 1);
    return true;
}

bool dcx(Register_Pair destination) {
    set_register_pair(destination, get_register_pair(destination) - 1);
    return true;
}

bool dad(Register_Pair source) {
    uint16_t h_value = get_register_pair(PAIR_H);
    set_register_pair(PAIR_H, (h_value + get_register_pair(source)) & 0xFFFF);
    bool carry = (h_value + get_register_pair(source)) > 0xFFFF;
    set_register_bit(REG_F, CARRY, carry);
    return true;
}

bool daa() {
    // Stolen from
    // https://github.com/GunshipPenguin/lib8080/blob/master/src/i8080.c
    // Line: 405 | I don't really know, what this mess does
    uint8_t add1 = 0;

    if (((get_register(REG_A) & 0xF) > 9) || get_register_bit(REG_F, AUXILIARY)) {
        add1 |= 0x06;
    }

    int carry = get_register_bit(REG_F, CARRY);
    /*
     * If the upper nibble is greater than 9
     * or the upper nibble will be greater than 9 when adding 6 to the lower nibble
     * or the carry flag is set
     */
    if (((get_register(REG_A) & 0xF0) > 0x90) ||
        (((get_register(REG_A) & 0xF0) >= 0x90) && ((get_register(REG_A) & 0xF) > 9)) ||
        get_register_bit(REG_F, CARRY)) {
        add1 |= 0x60;
        carry = 1;
    }

    set_register(REG_A, alu_add(get_register(REG_A), add1, false));

    // The carry bit is unaffected if there is no carry out of the upper nibble
    set_register_bit(REG_F, CARRY, carry);

    return true;
}

bool ana(Register source) {
    set_register(REG_A, alu_and(get_register(REG_A), get_register(source)));
    return true;
}

bool ani(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        set_register(REG_A, alu_and(get_register(REG_A), read(get_program_counter())));
        return true;
    }
    return false;
}

bool ora(Register source) {
    set_register(REG_A, alu_or(get_register(REG_A), get_register(source)));
    return true;
}

bool ori(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        set_register(REG_A, alu_or(get_register(REG_A), read(get_program_counter())));
        return true;
    }
    return false;
}

bool xra(Register source) {
    set_register(REG_A, alu_xor(get_register(REG_A), get_register(source)));
    return true;
}

bool xri(int machine_cycle) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        break;
    case 1:
        set_register(REG_A, alu_xor(get_register(REG_A), read(get_program_counter())));
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
        // printf("Instruction done\n");
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
