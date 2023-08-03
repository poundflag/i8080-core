#include <stdint.h>

/**
 * @file memory_controller.h
 * @brief Logic for memory read and write operations
 */
#ifndef _MEMORY_CONTROLLER_H_
#define _MEMORY_CONTROLLER_H_

/**
 * @brief Reads a byte from memory.
 *
 * @param[in] address The address to read from.
 * @return The data read from the memory cell.
 */
uint8_t read_from_memory(uint16_t address);

/**
 * @brief Writes a byte to memory.
 *
 * @param[in] address The address to write to.
 * @param[in] value The value to write at the address.
 */
void write_to_memory(uint16_t address, uint8_t value);

/**
 * @brief Loads memory with an array of data.
 *
 * This function loads an array of data into memory starting from the specified address offset.
 *
 * @param[in] file_data Pointer to the array of data.
 * @param[in] file_size The size of the data array.
 * @param[in] address_offset The offset indicating where the data writing should begin.
 *                           For example, an offset of 10 starts writing at address 10.
 */
void load_memory(uint8_t *file_data, long file_size, uint16_t address_offset);

#endif //_MEMORY_CONTROLLER_H_