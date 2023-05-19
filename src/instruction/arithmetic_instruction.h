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

// INR D     00DDD100          ZSPA    Increment register
bool inr(Register source);

// DCR D     00DDD101          ZSPA    Decrement register
bool dcr(Register source);

// INX RP    00RP0011          -       Increment register pair
bool inx(Register_Pair source);

// DCX RP    00RP1011          -       Decrement register pair
bool dcx(Register_Pair source);

#endif //_ARITHMETIC_INSTRUCTION_H_