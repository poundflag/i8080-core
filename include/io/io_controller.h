#include <stdint.h>

/**
 * @file io_controller.h
 * @brief Handles input and output operations.
 * @details Operates the I/O with a function pointer array, which allows the dynamic assignment of I/O devices based on the type definition
 * ::IO_Device.
 */
#ifndef _IO_CONTROLLER_H_
#define _IO_CONTROLLER_H_

/**
 * @brief Enumeration for I/O access modes.
 */
typedef enum {
    INPUT, /**< Input access mode. */
    OUTPUT /**< Output access mode. */
} ACCESS_MODE;
/**
 *
 * @typedef IO_Device
 * @brief Function pointer type for I/O device functions.
 * @param port_address The address of the I/O port.
 * @param access_mode The access mode (INPUT or OUTPUT) for the port.
 * @param value The value that is passed in a write operation.
 * @return The value read from or written to the port.
 */
typedef uint8_t (*IO_Device)(uint8_t port_address, uint8_t value, ACCESS_MODE access_mode);

/**
 * @brief Get the input device function pointer for a specific port.
 * @param port_address The address of the I/O port.
 * @return A pointer to the input device function for the specified port.
 */
IO_Device get_input_device(uint8_t port_address);

/**
 * @brief Set the input device function pointer for a specific port.
 * @param port_address The address of the I/O port.
 * @param io_device A pointer to the input device function.
 */
void set_input_device(uint8_t port_address, IO_Device io_device);

/**
 * @brief Read the value from a specific port.
 * @param port_address The address of the I/O port.
 * @return The value read from the port.
 */
uint8_t read_port(uint8_t port_address);

/**
 * @brief Write a value to a specific port.
 * @param port_address The address of the I/O port.
 * @param value The value to be written to the port.
 */
void write_port(uint8_t port_address, uint8_t value);

#endif // _IO_CONTROLLER_H_
