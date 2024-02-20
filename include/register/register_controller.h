#include <stdbool.h>
#include <stdint.h>

/**
 * @file register_controller.h
 * @brief Defines functions for manipulating registers and flags.
 */
#ifndef _REGISTER_CONTROLLER_H_
#define _REGISTER_CONTROLLER_H_

/**
 * @brief Enumeration of general-purpose registers and the flag register.
 */
typedef enum {
    REG_A,         ///< Accumulator Register A
    REG_B,         ///< General-purpose Register B
    REG_C,         ///< General-purpose Register C
    REG_D,         ///< General-purpose Register D
    REG_E,         ///< General-purpose Register E
    REG_H,         ///< General-purpose Register H
    REG_L,         ///< General-purpose Register L
    REG_F,         ///< Flags Register F
    REG_ENUM_SIZE, ///< Size of the Register enum
    REG_M          ///< Memory-Mapped Register M. Is outside of REG_ENUM_SIZE to avoid being looped.
} Register;

/**
 * @brief Enumeration of register pairs.
 */
typedef enum {
    PAIR_PSW,       ///< Program Status Word Register Pair
    PAIR_B,         ///< BC Register Pair
    PAIR_D,         ///< DE Register Pair
    PAIR_H,         ///< HL Register Pair
    PAIR_ENUM_SIZE, ///< Size of the Register_Pair enum
    PAIR_SP         ///< Stack Pointer Register Pair. Is outside of PAIR_ENUM_SIZE to avoid being looped.
} Register_Pair;

/**
 * @brief Enumeration of flag types within the flag register.
 */
typedef enum {
    CARRY = 0,     ///< Carry Flag
    PARITY = 2,    ///< Parity Flag
    AUXILIARY = 4, ///< Auxiliary Carry Flag
    ZERO = 6,      ///< Zero Flag
    SIGNED = 7     ///< Sign Flag
} Flag_Type;

/**
 * @brief Gets the value of a specified register.
 *
 * @param[in] destination The register from which to get the value.
 * @return The value stored in the register.
 */
uint8_t get_register(Register destination);

/**
 * @brief Sets the value of a specified register.
 *
 * @param[in] destination The register in which to set the value.
 * @param[in] value The value to set in the register.
 */
void set_register(Register destination, uint8_t value);

/**
 * @brief Gets the value of a specified register pair.
 *
 * @param[in] destination The register pair from which to get the value.
 * @return The value stored in the register pair.
 */
uint16_t get_register_pair(Register_Pair destination);

/**
 * @brief Sets the value of a specified register pair.
 *
 * @param[in] destination The register pair in which to set the value.
 * @param[in] value The value to set in the register pair.
 */
void set_register_pair(Register_Pair destination, uint16_t value);

/**
 * @brief Gets the value of the program counter.
 *
 * @return The value of the program counter.
 */
uint16_t get_program_counter();

/**
 * @brief Sets the value of the program counter.
 *
 * @param[in] value The value to set as the program counter.
 */
void set_program_counter(uint16_t value);

/**
 * @brief Increments the value of the program counter.
 */
void increment_program_counter();

/**
 * @brief Gets the state of a specific bit within a register.
 *
 * @param[in] register_source The register to check.
 * @param[in] bit_index The index of the bit to check.
 * @return The state of the specified bit.
 */
bool get_register_bit(Register register_source, int bit_index);

/**
 * @brief Sets the state of a specific bit within a register.
 *
 * @param[in] register_source The register to modify.
 * @param[in] bit_index The index of the bit to modify.
 * @param[in] state The desired state for the bit.
 */
void set_register_bit(Register register_source, int bit_index, bool state);

#endif //_REGISTER_CONTROLLER_H_
