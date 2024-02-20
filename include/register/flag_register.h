#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @file flag_register.h
 * @brief Functions to process and check flags within the flag register.
 */
#ifndef _FLAG_REGISTER_H_
#define _FLAG_REGISTER_H_

/**
 * @brief Enumeration of arithmetic operations that affect the flags. Defines the possible modes of arithmetic calculation.
 */
typedef enum {
    PLUS_OPERATION,       ///< Addition Operation
    SUBTRACTION_OPERATION ///< Subtraction Operation
} Arithmetic_Operation;

/**
 * @brief Checks if the result is zero.
 *
 * @param[in] result The result to check.
 * @return True if the result is zero, otherwise false.
 */
bool is_result_zero(uint8_t result);

/**
 * @brief Checks if the result is signed (negative).
 *
 * @param[in] result The result to check.
 * @return True if the result is negative, otherwise false.
 */
bool is_result_signed(uint8_t result);

/**
 * @brief Checks if the result has a parity (even number of set bits).
 *
 * @param[in] result The result to check.
 * @return True if the result has even parity, otherwise false.
 */
bool is_result_parity(uint8_t result);

/**
 * @brief Checks if the result generated a carry.
 *
 * @param[in] result The result to check.
 * @return True if the result generated a carry, otherwise false.
 */
bool is_result_carry(uint16_t result);

/**
 * @brief Checks if the result generated an auxiliary carry.
 *
 * @param[in] value_one The first value involved in the operation.
 * @param[in] value_two The second value involved in the operation.
 * @param[in] carry_bit The carry bit from a previous operation.
 * @return True if the result generated an auxiliary carry, otherwise false.
 */
bool is_result_auxiliary_carry(uint8_t value_one, uint8_t value_two, bool carry_bit);

/**
 * @brief Gets the result of the flag register based on the operation and inputs.
 *
 * This function gets the result of the flag register based on the provided values and operation. It doesn't set the flag register.
 *
 * @param[in] value_one The first value involved in the operation.
 * @param[in] value_two The second value involved in the operation.
 * @param[in] carry_flag The carry flag from a previous operation.
 * @param[in] operator The arithmetic operation being performed.
 * @return The value of the flag register after processing.
 */
uint8_t process_flag_register(uint8_t value_one, uint8_t value_two, bool carry_flag, Arithmetic_Operation operator);

#endif //_FLAG_REGISTER_H_
