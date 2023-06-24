#include <stdbool.h>
#include <stdint.h>

#ifndef _STATUS_SERVICE_H_
#define _STATUS_SERVICE_H_

bool is_stack_access();
void set_stack_access(bool state);
bool is_memory_read();
void set_memory_read(bool state);
bool is_first_machine_cycle();
void set_first_machine_cycle(bool state);
bool is_write_output();
void set_write_output(bool state);

#endif //_STATUS_SERVICE_H_