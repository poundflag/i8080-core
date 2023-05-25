#include <stdbool.h>
#include "../register/register_controller.h"

#ifndef _ARITHMETIC_INSTRUCTION_H_
#define _ARITHMETIC_INSTRUCTION_H_

// ADD S     10000SSS          ZSPCA   Add register to A
bool add(uint8_t source_value);

// ADI #     11000110 db       ZSCPA   Add immediate to A
bool adi(int machine_cycle);

// ADC S     10001SSS          ZSCPA   Add register to A with carry
bool adc(uint8_t source_value, bool carry_bit);

// ACI #     11001110 db       ZSCPA   Add immediate to A with carry
bool aci(bool carry_bit, int machine_cycle);

// SUB S     10010SSS          ZSCPA   Subtract register from A
bool sub(uint8_t source_value);

// SUI #     11010110 db       ZSCPA   Subtract immediate from A
bool sui(int machine_cycle);

// SBB S     10011SSS          ZSCPA   Subtract register from A with borrow
bool sbb(uint8_t source_value, bool carry_bit);

// SBI #     11011110 db       ZSCPA   Subtract immediate from A with borrow
bool sbi(bool carry_bit, int machine_cycle);

// INR D     00DDD100          ZSPA    Increment register TODO TEST THE FLAGS
bool inr(uint8_t* destination_value);

// DCR D     00DDD101          ZSPA    Decrement register TODO TEST THE FLAGS
bool dcr(uint8_t* destination_value);

// INX RP    00RP0011          -       Increment register pair TODO TEST THE FLAGS
bool inx(uint16_t* destination_value);

// DCX RP    00RP1011          -       Decrement register pair TODO TEST THE FLAGS
bool dcx(uint16_t* destination_value);

// DAD RP    00RP1001          C       Add register pair to HL (16 bit add) TODO TEST THE FLAGS
bool dad(uint16_t source_value);

// DAA       00100111          ZSPCA   Decimal Adjust accumulator
bool daa();

// ANA S     10100SSS          ZSCPA   AND register with A
bool ana(uint8_t source_value);

// ANI #     11100110 db       ZSPCA   AND immediate with A
bool ani(int machine_cycle);

// ORA S     10110SSS          ZSPCA   OR  register with A
bool ora(uint8_t source_value);

// ORI #     11110110          ZSPCA   OR  immediate with A
bool ori(int machine_cycle);

// XRA S     10101SSS          ZSPCA   ExclusiveOR register with A
bool xra(uint8_t source_value);

// XRI #     11101110 db       ZSPCA   ExclusiveOR immediate with A
bool xri(int machine_cycle);

// CMP S     10111SSS          ZSPCA   Compare register with A
bool cmp(uint8_t source_value);

// CPI #     11111110          ZSPCA   Compare immediate with A
bool cpi(int machine_cycle);

// RLC       00000111          C       Rotate A left
bool rlc();

// RRC       00001111          C       Rotate A right
bool rrc();

// RAL       00010111          C       Rotate A left through carry
bool ral();

// RAR       00011111          C       Rotate A right through carry
bool rar();

// CMA       00101111          -       Compliment A
bool cma();

// CMC       00111111          C       Compliment Carry flag
bool cmc();

// STC       00110111          C       Set Carry flag
bool stc();

#endif //_ARITHMETIC_INSTRUCTION_H_