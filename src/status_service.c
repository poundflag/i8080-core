#include "status_service.h"

bool stack_access = false;
bool memory_read = true;
bool first_machine_cycle = true;
bool write_output = false;

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

bool is_first_machine_cycle() {
    return first_machine_cycle;
}

void set_first_machine_cycle(bool state) {
    first_machine_cycle = state;
}

bool is_write_output() {
    return !write_output;
}

void set_write_output(bool state) {
    write_output = state;
}
