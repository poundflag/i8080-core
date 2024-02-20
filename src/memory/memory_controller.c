#include "memory/memory_controller.h"

uint8_t memory[0xFFFF] = {0};

uint8_t read_from_memory(uint16_t address) { return memory[address]; }

void write_to_memory(uint16_t address, uint8_t value) { memory[address] = value; }

void load_memory(uint8_t *file_data, long file_size, uint16_t address_offset) {
    for (int i = 0; i < file_size; i++) {
        write_to_memory(address_offset + i, file_data[i]);
    }
}
