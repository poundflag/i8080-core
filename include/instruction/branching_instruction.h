#include "../memory/memory_controller.h"
#include "../register/register_controller.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @file branching_instruction.h
 * @brief Defines branching instructions.
 */
#ifndef _BRANCHING_INSTRUCTION_H_
#define _BRANCHING_INSTRUCTION_H_

/**
 * @brief Defines different conditions for branching instructions.
 */
typedef enum {
    COND_CARRY,       ///< Carry flag is set
    COND_NO_CARRY,    ///< Carry flag is not set
    COND_MINUS,       ///< Negative (MSB of A is 1)
    COND_POSITIVE,    ///< Positive or zero (MSB of A is 0)
    COND_PARITY_EVEN, ///< Parity flag is even
    COND_PARITY_ODD,  ///< Parity flag is odd
    COND_ZERO,        ///< Zero flag is set
    COND_NOT_ZERO     ///< Zero flag is not set
} Condition;

/**
 * @brief Unconditionally jumps to the specified address.
 *
 * @details
 * Opcode: `11000011 lb hb`
 *
 * @param[in] machine_cycle The machine cycle containing the address.
 * @param[out] temporary_address The address to jump to.
 * @return True if the instruction finished, otherwise false.
 */
bool jmp(int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Conditionally jumps to the specified address based on the condition.
 *
 * @details
 * Opcode: `11CCC010 lb hb`
 *
 * @param[in] machine_cycle The machine cycle containing the address.
 * @param[out] temporary_address The address to jump to.
 * @param[in] condition The condition for the jump.
 * @return True if the instruction finished, otherwise false.
 */
bool jmp_conditional(int machine_cycle, uint16_t *temporary_address, Condition condition);

/**
 * @brief Unconditionally calls a subroutine at the specified address.
 *
 * @details
 * Opcode: `11001101 lb hb`
 *
 * @param[in] machine_cycle The machine cycle containing the address.
 * @param[out] temporary_address The address of the subroutine.
 * @return True if the instruction finished, otherwise false.
 */
bool call(int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Conditionally calls a subroutine at the specified address based on the condition.
 *
 * @details
 * Opcode: `11CCC100 lb hb`
 *
 * @param[in] machine_cycle The machine cycle containing the address.
 * @param[out] temporary_address The address of the subroutine.
 * @param[in] condition The condition for the call.
 * @return True if the instruction finished, otherwise false.
 */
bool call_conditional(int machine_cycle, uint16_t *temporary_address, Condition condition);

/**
 * @brief Unconditionally returns from a subroutine.
 *
 * @details
 * Opcode: `11001001`
 *
 * @return True if the instruction finished, otherwise false.
 */
bool ret();

/**
 * @brief Conditionally returns from a subroutine based on the condition.
 *
 * @details
 * Opcode: `11CCC000`
 *
 * @param[in] condition The condition for the return.
 * @return True if the instruction finished, otherwise false.
 */
bool ret_conditional(Condition condition);

/**
 * @brief Jumps to the address specified in the H:L register pair.
 *
 * @details
 * Opcode: `11101001`
 *
 * @return True if the instruction finished, otherwise false.
 */
bool pchl();

#endif //_BRANCHING_INSTRUCTION_H_
