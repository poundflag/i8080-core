#include <stdbool.h>

#ifndef _STATUS_SERVICE_H_
#define _STATUS_SERVICE_H_

bool is_stack_access();
void set_stack_access(bool state);
bool is_memory_read();
void set_memory_read(bool state);

#endif //_STATUS_SERVICE_H_