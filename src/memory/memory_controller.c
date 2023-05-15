#include "memory_controller.h"

uint8_t memory[0xFFFF] = { 0 };

uint8_t read(uint16_t address) {
    return memory[address];
}

void write(uint16_t address, uint8_t value) {
    memory[address] = value;
}