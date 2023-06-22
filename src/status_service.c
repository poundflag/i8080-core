#include "status_service.h"

bool stack_access = false;
bool memory_read = true;

bool is_stack_access() {
    return stack_access;
}

void set_stack_access(bool state) {
    stack_access = state;
}

bool is_memory_read() {
    return memory_read;
}

void set_memory_read(bool state) {
    memory_read = state;
}
