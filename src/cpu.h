#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef _CPU_H_
#define _CPU_H_

extern bool output_file;
extern char* file_path;

void run_indefinite();
void run(int steps);
void step(int* machine_cycle, uint16_t* temporary_address);
void load_file(char* file_path, uint16_t address_offset);

#endif //_CPU_H_