#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _CPU_H_
#define _CPU_H_

void run_indefinite();
void run(int steps);
void step();
void load_file(char* file_path, uint16_t address_offset);

#endif //_CPU_H_