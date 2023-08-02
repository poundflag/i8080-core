#include "../register/register_controller.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @file instruction.h
 * @brief Defines functions for decoding and executing instructions.
 */
#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

/**
 * @brief Decodes and executes the instruction based on the opcode.
 *
 * @details This function takes the opcode and performs the corresponding instruction execution.
 * It wont run the entire instruction but just the one machine cycle.
 * It also updates the temporary address and halt signal if necessary.
 *
 * @param[in] opcode The opcode of the instruction.
 * @param[in] machine_cycle The current machine cycle.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @param[out] halt_signal The halt signal that might be updated during execution.
 * @return True if the operation was successful, otherwise false.
 */
bool decode_execute_instruction(uint8_t opcode, int machine_cycle, uint16_t *temporary_address, bool *halt_signal);

/**
 * @brief Gets the destination register from the opcode.
 *
 * @param[in] opcode The opcode of the instruction.
 * @return The destination register specified in the opcode.
 */
Register get_destination_register(uint8_t opcode);

/**
 * @brief Gets the source register from the opcode.
 *
 * @param[in] opcode The opcode of the instruction.
 * @return The source register specified in the opcode.
 */
Register get_source_register(uint8_t opcode);

#endif //_INSTRUCTION_H_
