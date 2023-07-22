#include <stdint.h>

#ifndef _MEMORY_CONTROLLER_H_
#define _MEMORY_CONTROLLER_H_

uint8_t read_from_memory(uint16_t address);
void write_to_memory(uint16_t address, uint8_t value);
void load_memory(uint8_t *file_data, long file_size, uint16_t address_offset);

#endif //_MEMORY_CONTROLLER_H_