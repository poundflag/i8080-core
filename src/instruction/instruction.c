#include "instruction/instruction.h"
#include "instruction/arithmetic_instruction.h"
#include "instruction/branching_instruction.h"
#include "instruction/logical_instruction.h"

bool decode_execute_instruction(uint8_t opcode, int machine_cycle, uint16_t *temporary_address, bool *halt_signal) {
    switch (opcode) {
    case 0x00:
    case 0x10:
    case 0x20:
    case 0x30:
    case 0x08:
    case 0x18:
    case 0x28:
    case 0x38:
        return true;
    case 0x01:
        return lxi(PAIR_B, machine_cycle);
    case 0x11:
        return lxi(PAIR_D, machine_cycle);
    case 0x21:
        return lxi(PAIR_H, machine_cycle);
    case 0x31:
        return lxi(PAIR_SP, machine_cycle);
    case 0x02:
        return stax(PAIR_B, machine_cycle, temporary_address);
    case 0x12:
        return stax(PAIR_D, machine_cycle, temporary_address);
    case 0x22:
        return shld(machine_cycle, temporary_address);
    case 0x32:
        return sta(machine_cycle, temporary_address);
    case 0x03:
        return inx(PAIR_B);
    case 0x13:
        return inx(PAIR_D);
    case 0x23:
        return inx(PAIR_H);
    case 0x33:
        return inx(PAIR_SP);
    case 0x04:
    case 0x0C:
    case 0x14:
    case 0x1C:
    case 0x24:
    case 0x2C:
    case 0x34:
    case 0x3C:
        return inr(get_destination_register(opcode));
    case 0x05:
    case 0x0D:
    case 0x15:
    case 0x1D:
    case 0x25:
    case 0x2D:
    case 0x35:
    case 0x3D:
        return dcr(get_destination_register(opcode));
    case 0x0B:
        return dcx(PAIR_B);
    case 0x1B:
        return dcx(PAIR_D);
    case 0x2B:
        return dcx(PAIR_H);
    case 0x3B:
        return dcx(PAIR_SP);
    case 0x06:
    case 0x0E:
    case 0x16:
    case 0x1E:
    case 0x26:
    case 0x2E:
    case 0x36:
    case 0x3E:
        return mvi(get_destination_register(opcode), machine_cycle);
    case 0x07:
        return rlc();
    case 0x17:
        return ral();
    case 0x27:
        return daa();
    case 0x37:
        return stc();
    case 0x0F:
        return rrc();
    case 0x1F:
        return rar();
    case 0x2F:
        return cma();
    case 0x3F:
        return cmc();
    case 0x09:
        return dad(PAIR_B);
    case 0x19:
        return dad(PAIR_D);
    case 0x29:
        return dad(PAIR_H);
    case 0x39:
        return dad(PAIR_SP);
    case 0x0A:
        return ldax(PAIR_B, machine_cycle, temporary_address);
    case 0x1A:
        return ldax(PAIR_D, machine_cycle, temporary_address);
    case 0x2A:
        return lhld(machine_cycle, temporary_address);
    case 0x3A:
        return lda(machine_cycle, temporary_address);
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x5E:
    case 0x5F:
    case 0x60:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x6D:
    case 0x6E:
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x7B:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
        return mov(get_destination_register(opcode), get_source_register(opcode));
    case 0x76:
        printf("True");
        *halt_signal = true;
        return true;
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
        return add(get_source_register(opcode));
    case 0x88:
    case 0x89:
    case 0x8A:
    case 0x8B:
    case 0x8C:
    case 0x8D:
    case 0x8E:
    case 0x8F:
        return adc(get_source_register(opcode));
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
        return sub(get_source_register(opcode));
    case 0x98:
    case 0x99:
    case 0x9A:
    case 0x9B:
    case 0x9C:
    case 0x9D:
    case 0x9E:
    case 0x9F:
        return sbb(get_source_register(opcode));
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
    case 0xA4:
    case 0xA5:
    case 0xA6:
    case 0xA7:
        return ana(get_source_register(opcode));
    case 0xA8:
    case 0xA9:
    case 0xAA:
    case 0xAB:
    case 0xAC:
    case 0xAD:
    case 0xAE:
    case 0xAF:
        return xra(get_source_register(opcode));
    case 0xB0:
    case 0xB1:
    case 0xB2:
    case 0xB3:
    case 0xB4:
    case 0xB5:
    case 0xB6:
    case 0xB7:
        return ora(get_source_register(opcode));
    case 0xB8:
    case 0xB9:
    case 0xBA:
    case 0xBB:
    case 0xBC:
    case 0xBD:
    case 0xBE:
    case 0xBF:
        return cmp(get_source_register(opcode));
    case 0xC0:
        return ret_conditional(COND_NOT_ZERO);
    case 0xC8:
        return ret_conditional(COND_ZERO);
    case 0xD0:
        return ret_conditional(COND_NO_CARRY);
    case 0xD8:
        return ret_conditional(COND_CARRY);
    case 0xE0:
        return ret_conditional(COND_PARITY_ODD);
    case 0xE8:
        return ret_conditional(COND_PARITY_EVEN);
    case 0xF0:
        return ret_conditional(COND_POSITIVE);
    case 0xF8:
        return ret_conditional(COND_MINUS);
    case 0xC1:
        return pop(PAIR_B, machine_cycle, temporary_address);
    case 0xD1:
        return pop(PAIR_D, machine_cycle, temporary_address);
    case 0xE1:
        return pop(PAIR_H, machine_cycle, temporary_address);
    case 0xF1:
        return pop(PAIR_PSW, machine_cycle, temporary_address);
    case 0xC2:
        return jmp_conditional(machine_cycle, temporary_address, COND_NOT_ZERO);
    case 0xD2:
        return jmp_conditional(machine_cycle, temporary_address, COND_NO_CARRY);
    case 0xE2:
        return jmp_conditional(machine_cycle, temporary_address, COND_PARITY_ODD);
    case 0xF2:
        return jmp_conditional(machine_cycle, temporary_address, COND_POSITIVE);
    case 0xCA:
        return jmp_conditional(machine_cycle, temporary_address, COND_ZERO);
    case 0xDA:
        return jmp_conditional(machine_cycle, temporary_address, COND_CARRY);
    case 0xEA:
        return jmp_conditional(machine_cycle, temporary_address, COND_PARITY_EVEN);
    case 0xFA:
        return jmp_conditional(machine_cycle, temporary_address, COND_MINUS);
    case 0xCB:
    case 0xC3:
        return jmp(machine_cycle, temporary_address);
    case 0xD3:
        return out(machine_cycle);
    case 0xE3:
        return xthl();
    case 0xF3:
        // TODO IMPLEMENT
        return true;
    case 0xC4:
        return call_conditional(machine_cycle, temporary_address, COND_NOT_ZERO);
    case 0xD4:
        return call_conditional(machine_cycle, temporary_address, COND_NO_CARRY);
    case 0xE4:
        return call_conditional(machine_cycle, temporary_address, COND_PARITY_ODD);
    case 0xF4:
        return call_conditional(machine_cycle, temporary_address, COND_POSITIVE);
    case 0xCC:
        return call_conditional(machine_cycle, temporary_address, COND_ZERO);
    case 0xDC:
        return call_conditional(machine_cycle, temporary_address, COND_CARRY);
    case 0xEC:
        return call_conditional(machine_cycle, temporary_address, COND_PARITY_EVEN);
    case 0xFC:
        return call_conditional(machine_cycle, temporary_address, COND_MINUS);
    case 0xC5:
        return push(PAIR_B, machine_cycle, temporary_address);
    case 0xD5:
        return push(PAIR_D, machine_cycle, temporary_address);
    case 0xE5:
        return push(PAIR_H, machine_cycle, temporary_address);
    case 0xF5:
        return push(PAIR_PSW, machine_cycle, temporary_address);
    case 0xC6:
        return adi(machine_cycle);
    case 0xD6:
        return sui(machine_cycle);
    case 0xE6:
        return ani(machine_cycle);
    case 0xF6:
        return ori(machine_cycle);
    case 0xCE:
        return aci(machine_cycle);
    case 0xDE:
        return sbi(machine_cycle);
    case 0xEE:
        return xri(machine_cycle);
    case 0xFE:
        return cpi(machine_cycle);
    case 0xC7:
        return rst(0);
    case 0xD7:
        return rst(2);
    case 0xE7:
        return rst(4);
    case 0xF7:
        return rst(6);
    case 0xCF:
        return rst(1);
    case 0xDF:
        return rst(3);
    case 0xEF:
        return rst(5);
    case 0xFF:
        return rst(7);
    case 0xC9:
    case 0xD9:
        return ret();
    case 0xE9:
        return pchl();
    case 0xF9:
        return sphl();
    case 0xDB:
        return in(machine_cycle);
    case 0xEB:
        return xchg();
        // TODO Implement
    case 0xFB:
        return true;
    case 0xCD:
    case 0xDD:
    case 0xED:
    case 0xFD:
        return call(machine_cycle, temporary_address);
    }
    return true;
}

Register get_destination_register(uint8_t opcode) {
    uint8_t higher_nibble = (opcode >> 4) % 4;
    uint8_t lower_nibble = opcode & 0xF;

    if (higher_nibble == 0 && lower_nibble <= 0x7) {
        return REG_B;
    } else if (higher_nibble == 0 && lower_nibble > 0x7) {
        return REG_C;
    } else if (higher_nibble == 1 && lower_nibble <= 0x7) {
        return REG_D;
    } else if (higher_nibble == 1 && lower_nibble > 0x7) {
        return REG_E;
    } else if (higher_nibble == 2 && lower_nibble <= 0x7) {
        return REG_H;
    } else if (higher_nibble == 2 && lower_nibble > 0x7) {
        return REG_L;
    } else if (higher_nibble == 3 && lower_nibble <= 0x7) {
        return REG_M;
    } else if (higher_nibble == 3 && lower_nibble > 0x7) {
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
        return REG_M;
    case 7:
        return REG_A;
    }
    return 0;
}
