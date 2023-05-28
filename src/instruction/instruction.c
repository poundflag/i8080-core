#include "instruction.h"
#include "logical_instruction.h"
#include "arithmetic_instruction.h"

int machine_cycle = 0;

void reset_machine_cycle() {
    machine_cycle = 0;
    increment_program_counter();
}

void decode_execute_instruction(uint8_t opcode) {
    if (opcode >= 0x40 && opcode <= 0x7F && opcode != 0x76) {
        mov(get_destination_register(opcode), get_source_register(opcode));
    } else if (opcode >= 0x80 && opcode <= 0x87) {
        add(get_source_register(opcode));
    } else if (opcode >= 0x80 && opcode <= 0x87) {
        adc(get_source_register(opcode));
    } else if (opcode >= 0x80 && opcode <= 0x87) {
        sub(get_source_register(opcode));
    } else if (opcode >= 0x80 && opcode <= 0x87) {
        sbb(get_source_register(opcode));
    } else if (opcode >= 0x80 && opcode <= 0x87) {
        ana(get_source_register(opcode));
    } else if (opcode >= 0x80 && opcode <= 0x87) {
        xra(get_source_register(opcode));
    } else if (opcode >= 0x80 && opcode <= 0x87) {
        ora(get_source_register(opcode));
    } else if (opcode >= 0x80 && opcode <= 0x87) {
        cmp(get_source_register(opcode));
    }
}

Register get_destination_register(uint8_t opcode) {
    uint8_t higher_nibble = (opcode >> 4) % 4;
    uint8_t lower_nibble = opcode & 0xF;

    if (higher_nibble == 0 && lower_nibble <= 0x7) {
        return REG_B;
    }
    else if (higher_nibble == 0 && lower_nibble > 0x7) {
        return REG_C;
    }
    else if (higher_nibble == 1 && lower_nibble <= 0x7) {
        return REG_D;
    }
    else if (higher_nibble == 1 && lower_nibble > 0x7) {
        return REG_E;
    }
    else if (higher_nibble == 2 && lower_nibble <= 0x7) {
        return REG_H;
    }
    else if (higher_nibble == 2 && lower_nibble > 0x7) {
        return REG_L;
    }
    else if (higher_nibble == 3 && lower_nibble <= 0x7) {
        return REG_H;
    }
    else if (higher_nibble == 3 && lower_nibble > 0x7) {
        return REG_A;
    }
    return 0;
}

Register get_source_register(uint8_t opcode) {
    switch ((opcode & 0xF) % 8) {
    case 0:
        return REG_B;
    case 1:
        return REG_C;
    case 2:
        return REG_D;
    case 3:
        return REG_E;
    case 4:
        return REG_H;
    case 5:
        return REG_L;
    case 6:
        return REG_H;
    case 7:
        return REG_A;
    }
    return 0;
}
