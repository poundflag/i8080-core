#include <stdint.h>

/**
 * @file stack.h
 * @brief Functions for managing the stack operations.
 */
#ifndef _STACK_H_
#define _STACK_H_

/**
 * @brief Gets the current value of the stack pointer.
 *
 * @return The value of the stack pointer.
 */
uint16_t get_stack_pointer();

/**
 * @brief Sets the value of the stack pointer.
 *
 * @param[in] stack_pointer_address The address to set as the stack pointer.
 */
void set_stack_pointer(uint16_t stack_pointer_address);

/**
 * @brief Pushes a 16-bit word onto the stack.
 *
 * @param[in] word_value The 16-bit value to push onto the stack.
 */
void push_word(uint16_t word_value);

/**
 * @brief Pulls a 16-bit word from the stack.
 *
 * @return The 16-bit word pulled from the stack.
 */
uint16_t pull_word();

#endif //_STACK_H_
