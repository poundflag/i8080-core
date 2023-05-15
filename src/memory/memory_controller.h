#include <stdint.h>

#ifndef _MEMORY_CONTROLLER_H_
#define _MEMORY_CONTROLLER_H_

uint8_t read(uint16_t address);
void write(uint16_t address, uint8_t value);

#endif //_MEMORY_CONTROLLER_H_