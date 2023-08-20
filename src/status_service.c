#include "status_service.h"

bool stack_access = false;
bool memory_read = true;
bool first_machine_cycle = true;
bool write_output = false;
bool device_output = false;
bool device_input = false;
bool halt_signal = false;

bool is_stack_access() { return stack_access; }

void set_stack_access(bool state) { stack_access = state; }

bool is_memory_read() { return memory_read; }

void set_memory_read(bool state) { memory_read = state; }

bool is_first_machine_cycle() { return first_machine_cycle; }

void set_first_machine_cycle(bool state) { first_machine_cycle = state; }

bool is_write_output() { return !write_output; }

void set_write_output(bool state) { write_output = state; }

bool is_device_output() { return device_output; }

void set_device_output(bool state) { device_output = state; }

bool is_device_input() { return device_input; }

void set_device_input(bool state) { device_input = state; }

bool has_system_halted() { return halt_signal; }

void set_system_halt(bool system_halt) { halt_signal = system_halt; }