#include "../register/register_controller.h"
#include <stdbool.h>

/**
 * @file arithmetic_instruction.h
 * @brief Defines various arithmetic instructions.
 */
#ifndef _ARITHMETIC_INSTRUCTION_H_
#define _ARITHMETIC_INSTRUCTION_H_

/**
 * @brief Adds the value of a specified register to the accumulator (A).
 *
 * @details
 * Opcode: `10000SSS`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] source The source register to be added to A.
 * @return True if the instruction finished, otherwise false.
 */
bool add(Register source);

/**
 * @brief Adds an immediate value to the accumulator (A) with carry.
 *
 * @details
 * Opcode: `11000110 db`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool adi(int machine_cycle);

/**
 * @brief Adds the value of a specified register to A with carry.
 *
 * @details
 * Opcode: `10001SSS`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] source The source register to be added to A.
 * @return True if the instruction finished, otherwise false.
 */
bool adc(Register source);

/**
 * @brief Adds an immediate value to A with carry.
 *
 * @details
 * Opcode: `11001110 db`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool aci(int machine_cycle);

/**
 * @brief Subtracts the value of a specified register from the accumulator (A).
 *
 * @details
 * Opcode: `10010SSS`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] source The source register to be subtracted from A.
 * @return True if the instruction finished, otherwise false.
 */
bool sub(Register source);

/**
 * @brief Subtracts an immediate value from the accumulator (A).
 *
 * @details
 * Opcode: `11010110 db`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool sui(int machine_cycle);

/**
 * @brief Subtracts the value of a specified register from A with borrow.
 *
 * @details
 * Opcode: `10011SSS`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] source The source register to be subtracted from A.
 * @return True if the instruction finished, otherwise false.
 */
bool sbb(Register source);

/**
 * @brief Subtracts an immediate value from A with borrow.
 *
 * @details
 * Opcode: `11011110 db`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool sbi(int machine_cycle);

/**
 * @brief Increments the specified register.
 *
 * @details
 * Opcode: `00DDD100`
 * Flags Affected: Z, S, P, A
 *
 * @param[in] destination The register to be incremented.
 * @return True if the instruction finished, otherwise false.
 */
bool inr(Register destination);

/**
 * @brief Decrements the specified register.
 *
 * @details
 * Opcode: `00DDD101`
 * Flags Affected: Z, S, P, A
 *
 * @param[in] destination The register to be decremented.
 * @return True if the instruction finished, otherwise false.
 */
bool dcr(Register destination);

/**
 * @brief Increments the specified register pair.
 *
 * @details
 * Opcode: `00RP0011`
 *
 * @param[in] destination The register pair to be incremented.
 * @return True if the instruction finished, otherwise false.
 */
bool inx(Register_Pair destination);

/**
 * @brief Decrements the specified register pair.
 *
 * @details
 * Opcode: `00RP1011`
 *
 * @param[in] destination The register pair to be decremented.
 * @return True if the instruction finished, otherwise false.
 */
bool dcx(Register_Pair destination);

/**
 * @brief Adds the value of the specified register pair to HL (16-bit addition).
 *
 * @details
 * Opcode: `00RP1001`
 * Flags Affected: C
 *
 * @param[in] source The source register pair to be added to HL.
 * @return True if the instruction finished, otherwise false.
 */
bool dad(Register_Pair source);

/**
 * @brief Performs decimal adjust on the accumulator (A) after addition.
 *
 * @details
 * Opcode: `00100111`
 * Flags Affected: Z, S, P, C, A
 *
 * @return True if the instruction finished, otherwise false.
 */
bool daa();

/**
 * @brief Performs bitwise AND between the accumulator (A) and the specified register.
 *
 * @details
 * Opcode: `10100SSS`
 * Flags Affected: Z, S, P, C
 *
 * @param[in] source The source register to be ANDed with A.
 * @return True if the instruction finished, otherwise false.
 */
bool ana(Register source);

/**
 * @brief Performs bitwise AND between the accumulator (A) and an immediate value.
 *
 * @details
 * Opcode: `11100110 db`
 * Flags Affected: Z, S, P, C
 *
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool ani(int machine_cycle);

/**
 * @brief Performs bitwise OR between the accumulator (A) and the specified register.
 *
 * @details
 * Opcode: `10110SSS`
 * Flags Affected: Z, S, P, C
 *
 * @param[in] source The source register to be ORed with A.
 * @return True if the instruction finished, otherwise false.
 */
bool ora(Register source);

/**
 * @brief Performs bitwise OR between the accumulator (A) and an immediate value.
 *
 * @details
 * Opcode: `11110110`
 * Flags Affected: Z, S, P, C
 *
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool ori(int machine_cycle);

/**
 * @brief Performs exclusive OR between the accumulator (A) and the specified register.
 *
 * @details
 * Opcode: `10101SSS`
 * Flags Affected: Z, S, P, C
 *
 * @param[in] source The source register to be XORed with A.
 * @return True if the instruction finished, otherwise false.
 */
bool xra(Register source);

/**
 * @brief Performs exclusive OR between the accumulator (A) and an immediate value.
 *
 * @details
 * Opcode: `11101110 db`
 * Flags Affected: Z, S, P, C
 *
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool xri(int machine_cycle);

/**
 * @brief Compares the accumulator (A) with the specified register.
 *
 * @details
 * Opcode: `10111SSS`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] source The source register to be compared with A.
 * @return True if the instruction finished, otherwise false.
 */
bool cmp(Register source);

/**
 * @brief Compares the accumulator (A) with an immediate value.
 *
 * @details
 * Opcode: `11111110`
 * Flags Affected: Z, S, P, C, A
 *
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool cpi(int machine_cycle);

/**
 * @brief Rotates the accumulator (A) left through carry.
 *
 * @details
 * Opcode: `00000111`
 * Flags Affected: C
 *
 * @return True if the instruction finished, otherwise false.
 */
bool rlc();

/**
 * @brief Rotates the accumulator (A) right through carry.
 *
 * @details
 * Opcode: `00001111`
 * Flags Affected: C
 *
 * @return True if the instruction finished, otherwise false.
 */
bool rrc();

/**
 * @brief Rotates the accumulator (A) left through carry.
 *
 * @details
 * Opcode: `00010111`
 * Flags Affected: C
 *
 * @return True if the instruction finished, otherwise false.
 */
bool ral();

/**
 * @brief Rotates the accumulator (A) right through carry.
 *
 * @details
 * Opcode: `00011111`
 * Flags Affected: C
 *
 * @return True if the instruction finished, otherwise false.
 */
bool rar();

/**
 * @brief Complements the accumulator (A).
 *
 * @details
 * Opcode: `00101111`
 *
 * @return True if the instruction finished, otherwise false.
 */
bool cma();

/**
 * @brief Complements the carry flag.
 *
 * @details
 * Opcode: `00111111`
 * Flags Affected: C
 *
 * @return True if the instruction finished, otherwise false.
 */
bool cmc();

/**
 * @brief Sets the carry flag.
 *
 * @details
 * Opcode: `00110111`
 * Flags Affected: C
 *
 * @return True if the instruction finished, otherwise false.
 */
bool stc();

#endif //_ARITHMETIC_INSTRUCTION_H_
