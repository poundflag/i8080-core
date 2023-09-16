#include <stdint.h>

/**
 * @file bus_controller.h
 * @brief The main interface to get data like the state of the cpu or the data and address bus.
 */

#ifndef _BUS_CONTROLLER_H_
#define _BUS_CONTROLLER_H_

/**
 * @return The current data that's placed on the address bus.
 */
uint16_t get_address_bus();

/**
 * @return The current data that's placed on the data bus.
 */
uint8_t get_data_bus();

#endif //_BUS_CONTROLLER_H_
