#include <stdbool.h>
#include "../register/register_controller.h"

#ifndef _ARITHMETIC_INSTRUCTION_H_
#define _ARITHMETIC_INSTRUCTION_H_

// ADD S     10000SSS          ZSPCA   Add register to A
bool add(Register source);

// ADI #     11000110 db       ZSCPA   Add immediate to A
bool adi(int machine_cycle);

// ADC S     10001SSS          ZSCPA   Add register to A with carry
bool adc(Register source, bool carry_bit);

// ACI #     11001110 db       ZSCPA   Add immediate to A with carry
bool aci(bool carry_bit, int machine_cycle);

// SUB S     10010SSS          ZSCPA   Subtract register from A
bool sub(Register source);

// SUI #     11010110 db       ZSCPA   Subtract immediate from A
bool sui(int machine_cycle);

// SBB S     10011SSS          ZSCPA   Subtract register from A with borrow
bool sbb(Register source, bool carry_bit);

// SBI #     11011110 db       ZSCPA   Subtract immediate from A with borrow
bool sbi(bool carry_bit, int machine_cycle);

// INR D     00DDD100          ZSPA    Increment register TODO TEST THE FLAGS
bool inr(Register source);

// DCR D     00DDD101          ZSPA    Decrement register TODO TEST THE FLAGS
bool dcr(Register source);

// INX RP    00RP0011          -       Increment register pair TODO TEST THE FLAGS
bool inx(Register_Pair source);

// DCX RP    00RP1011          -       Decrement register pair TODO TEST THE FLAGS
bool dcx(Register_Pair source);

// DAD RP    00RP1001          C       Add register pair to HL (16 bit add) TODO TEST THE FLAGS
bool dad(Register_Pair source);

// DAA       00100111          ZSPCA   Decimal Adjust accumulator
bool daa();

// ANA S     10100SSS          ZSCPA   AND register with A
bool ana(Register source);

// ANI #     11100110 db       ZSPCA   AND immediate with A
bool ani(int machine_cycle);

// ORA S     10110SSS          ZSPCA   OR  register with A
bool ora(Register source);

// ORI #     11110110          ZSPCA   OR  immediate with A
bool ori(int machine_cycle);

// XRA S     10101SSS          ZSPCA   ExclusiveOR register with A
bool xra(Register source);

// XRI #     11101110 db       ZSPCA   ExclusiveOR immediate with A
bool xri(int machine_cycle);

// CMP S     10111SSS          ZSPCA   Compare register with A
bool cmp(Register source);

// CPI #     11111110          ZSPCA   Compare immediate with A
bool cpi(int machine_cycle);

// RLC       00000111          C       Rotate A left
bool rlc();

#endif //_ARITHMETIC_INSTRUCTION_H_