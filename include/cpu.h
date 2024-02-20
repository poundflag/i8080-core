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
 * @param[in, out] opcode The current opcode to execute
 *
 */
void step(int *machine_cycle, uint8_t *opcode);

/**
 * @brief Loads a binary file into the system's memory.
 *
 * @param[in] file_path The path of the binary file to load.
 * @param[in] address_offset The offset indicating where data writing should begin.
 *                           For example, an offset of 10 starts writing at address 10.
 */
void load_file(char *file_path, uint16_t address_offset);

#endif //_CPU_H_
