#include <stdbool.h>
#include <stdint.h>

/**
 * @file status_service.h
 * @brief Sets and resets the status of serveral cpu services.
 */

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
bool is_device_output();
void set_device_output(bool state);
bool is_device_input();
void set_device_input(bool state);

/**
 * @brief Reports whether the system has executed a HLT instruction and halted.
 *
 * @return If true, the system has halted and can't execute further instructions.
 */
bool has_system_halted();

/**
 * @brief Manually sets the system's halted state.
 *
 * @param[in] system_halt If true, the system is halted.
 */
void set_system_halt(bool system_halt);

#endif //_STATUS_SERVICE_H_