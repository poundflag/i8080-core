#include "branching_instruction.h"
#include "../register/stack.h"

bool jmp(int machine_cycle, uint16_t* temporary_address) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        *temporary_address = read(get_program_counter());
        break;
    case 1:
        increment_program_counter();
        *temporary_address |= read(get_program_counter()) << 8;
        break;
    case 2:
        set_program_counter(*temporary_address - 1);
        return true;
        break;
    default:
        break;
    }
    return false;
}

bool condition_success(Condition condition) {
    switch (condition) {
    case COND_CARRY:
        return get_register_bit(REG_F, CARRY) == true;
    case COND_NO_CARRY:
        return get_register_bit(REG_F, CARRY) == false;
    case COND_MINUS:
        return get_register_bit(REG_F, SIGNED) == true;
    case COND_POSITIVE:
        return get_register_bit(REG_F, SIGNED) == false;
    case COND_PARITY_EVEN:
        return get_register_bit(REG_F, PARITY) == true;
    case COND_PARITY_ODD:
        return get_register_bit(REG_F, PARITY) == false;
    case COND_ZERO:
        return get_register_bit(REG_F, ZERO) == true;
    case COND_NOT_ZERO:
        return get_register_bit(REG_F, ZERO) == false;
    default:
        break;
    }
    return false;
}

bool jmp_conditional(int machine_cycle, uint16_t* temporary_address, Condition condition) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        *temporary_address = read(get_program_counter());
        break;
    case 1:
        increment_program_counter();
        *temporary_address |= read(get_program_counter()) << 8;
        break;
    case 2:
        if (condition_success(condition)) {
            set_program_counter(*temporary_address - 1);
        }
        return true;
    default:
        break;
    }
    return false;
}

bool call(int machine_cycle, uint16_t* temporary_address) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        *temporary_address = read(get_program_counter());
        break;
    case 1:
        increment_program_counter();
        *temporary_address |= read(get_program_counter()) << 8;
        break;
    case 2:
        push_word(get_program_counter() + 1);
        set_program_counter(*temporary_address - 1);
        return true;
    default:
        break;
    }
    return false;
}

bool call_conditional(int machine_cycle, uint16_t* temporary_address, Condition condition) {
    switch (machine_cycle) {
    case 0:
        increment_program_counter();
        *temporary_address = read(get_program_counter());
        break;
    case 1:
        increment_program_counter();
        *temporary_address |= read(get_program_counter()) << 8;
        break;
    case 2:
        if (condition_success(condition)) {
            push_word(get_program_counter() + 1);
            set_program_counter(*temporary_address - 1);
        }
        return true;
    default:
        break;
    }
    return false;
}

bool ret() {
    set_program_counter(pull_word() - 1);
    return true;
}

bool ret_conditional(Condition condition) {
    if (condition_success(condition)) {
        set_program_counter(pull_word() - 1);
    }
    return true;
}

bool pchl() {
    set_program_counter(get_register_pair(PAIR_H) - 1);
    return true;
}
