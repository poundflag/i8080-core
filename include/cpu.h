#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file cpu.h
 * @brief Defines the core functionalities for the emulator's CPU operations.
 */

#ifndef _CPU_H_
#define _CPU_H_

/**
 * @brief Specifies whether the state after each instruction cycle should be logged to a file or not.
 */
extern bool output_file;

/**
 * @brief File path for logging the output.
 */
extern char *file_path;

/**
 * @brief Indefinitely runs the CPU, stopping only when encountering the HLT instruction.
 */
void run_indefinite();

/**
 * @brief Runs the CPU for a specified number of steps, performing a full instruction cycle on each step.
 *
 * @param[in] steps The number of steps to execute.
 */
void run(int steps);

/**
 * @brief Steps through the CPU for each hardware cycle.
 *
 * This method requires additional setup. For single instructions, consider using @ref run(int steps).
 *
 * @param[in, out] machine_cycle The current machine cycle of the instruction to execute.
 * @param[out] temporary_address A cache for temporary addresses saved between hardware cycles (e.g., PUSH instruction).
 * @todo Add opcode parameter
 */
void step(int *machine_cycle, uint16_t *temporary_address);

/**
 * @brief Loads a binary file into the system's memory.
 *
 * @param[in] file_path The path of the binary file to load.
 * @param[in] address_offset The offset indicating where data writing should begin.
 *                           For example, an offset of 10 starts writing at address 10.
 */
void load_file(char *file_path, uint16_t address_offset);

/**
 * @brief Reports whether the system has executed a HLT instruction and halted.
 *
 * @return If true, the system has halted and can't execute further instructions.
 */
bool has_system_halted();

/**
 * @brief Manually sets the system's halted state.
 *
 * @param[in] system_halt If true, the system is halted.
 */
void set_system_halt(bool system_halt);

#endif //_CPU_H_
