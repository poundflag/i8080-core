#include "../register/register_controller.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @file logical_instruction.h
 * @brief Defines various logical instructions.
 */
#ifndef _LOGICAL_INSTRUCTION_H_
#define _LOGICAL_INSTRUCTION_H_

/**
 * @brief Moves the value of the source register into the destination register.
 *
 * @details
 * Opcode: `01DDDSSS`
 *
 * @param[in] destination The destination register.
 * @param[in] source The source register.
 * @return True if the instruction finished, otherwise false.
 */
bool mov(Register destination, Register source);

/**
 * @brief Moves an immediate value into the specified register.
 *
 * @details
 * Opcode: `00DDD110 db`
 *
 * @param[in] destination The destination register.
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool mvi(Register destination, int machine_cycle);

/**
 * @brief Loads an immediate value into the specified register pair.
 *
 * @details
 * Opcode: `00RP0001 lb hb`
 *
 * @param[in] destination The destination register pair.
 * @param[in] machine_cycle The machine cycle containing the immediate value.
 * @return True if the instruction finished, otherwise false.
 */
bool lxi(Register_Pair destination, int machine_cycle);

/**
 * @brief Loads the value from memory address into the accumulator (A).
 *
 * @details
 * Opcode: `00111010 lb hb`
 *
 * @param[in] machine_cycle The machine cycle containing the memory address.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @return True if the instruction finished, otherwise false.
 */
bool lda(int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Stores the value of the accumulator (A) into a memory address.
 *
 * @details
 * Opcode: `00110010 lb hb`
 *
 * @param[in] machine_cycle The machine cycle containing the memory address.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @return True if the instruction finished, otherwise false.
 */
bool sta(int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Loads H:L from a memory address.
 *
 * @details
 * Opcode: `00101010 lb hb`
 *
 * @param[in] machine_cycle The machine cycle containing the memory address.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @return True if the instruction finished, otherwise false.
 */
bool lhld(int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Stores H:L to a memory address.
 *
 * @details
 * Opcode: `00100010 lb hb`
 *
 * @param[in] machine_cycle The machine cycle containing the memory address.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @return True if the instruction finished, otherwise false.
 */
bool shld(int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Loads a value from memory addressed by register pair into the accumulator (A).
 *
 * @details
 * Opcode: `00RP1010 *1`
 *
 * @param[in] indirect_pair The indirect register pair (BC or DE).
 * @param[in] machine_cycle The current machine cycle.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @return True if the instruction finished, otherwise false.
 */
bool ldax(Register_Pair indirect_pair, int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Stores the value of the accumulator (A) into memory addressed by register pair.
 *
 * @details
 * Opcode: `00RP0010 *1`
 *
 * @param[in] indirect_pair The indirect register pair (BC or DE).
 * @param[in] machine_cycle The current machine cycle.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @return True if the instruction finished, otherwise false.
 */
bool stax(Register_Pair indirect_pair, int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Exchanges the contents of DE and HL registers.
 *
 * @details
 * Opcode: `11101011`
 *
 * @return True if the instruction finished, otherwise false.
 */
bool xchg();

/**
 * @brief Restarts the CPU by performing a subroutine call to the specified address.
 *
 * @details
 * Opcode: `11NNN111`
 *
 * @param[in] number The restart number (n) multiplied by 8.
 * @return True if the instruction finished, otherwise false.
 */
bool rst(int number);

/**
 * @brief Pushes the contents of the specified register pair onto the stack.
 *
 * @details
 * Opcode: `11RP0101 *2`
 *
 * @param[in] register_pair The register pair to push.
 * @param[in] machine_cycle The current machine cycle.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @return True if the instruction finished, otherwise false.
 */
bool push(Register_Pair register_pair, int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Pops the contents from the stack into the specified register pair.
 *
 * @details
 * Opcode: `11RP0001 *2`
 *
 * @param[in] register_pair The register pair to pop into.
 * @param[in] machine_cycle The current machine cycle.
 * @param[out] temporary_address The temporary address that might be updated during execution.
 * @return True if the instruction finished, otherwise false.
 */
bool pop(Register_Pair register_pair, int machine_cycle, uint16_t *temporary_address);

/**
 * @brief Swaps the contents of H:L register pair with the top word on the stack.
 *
 * @details
 * Opcode: `11100011`
 *
 * @return True if the instruction finished, otherwise false.
 */
bool xthl();

/**
 * @brief Sets the stack pointer (SP) to the contents of H:L register pair.
 *
 * @details
 * Opcode: `11111001`
 *
 * @return True if the instruction finished, otherwise false.
 */
bool sphl();

/**
 * @brief Reads input data from a specified port into the accumulator (A).
 *
 * @details
 * Opcode: `11011011 pa`
 *
 * @param[in] port_number The port number to read from.
 * @return True if the instruction finished, otherwise false.
 */
bool in(uint8_t port_number);

/**
 * @brief Writes the contents of the accumulator (A) to a specified port.
 *
 * @details
 * Opcode: `11010011 pa`
 *
 * @param[in] port_number The port number to write to.
 * @return True if the instruction finished, otherwise false.
 */
bool out(uint8_t port_number);

/**
 * @brief Halts the processor, stopping further execution.
 *
 * @details
 * Opcode: `01110110`
 *
 * @return True if the instruction finished, otherwise false.
 */
bool hlt();

#endif //_LOGICAL_INSTRUCTION_H_