#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @file file_io.h
 * @brief Defines file input/output operations for interacting with the actual system.
 */

#ifndef _FILE_IO_H_
#define _FILE_IO_H_

/**
 * @struct File_Response
 * @brief Response structure to manage data read from a file.
 */
typedef struct {
    uint8_t *file_data; ///< Pointer to the data read from the file.
    size_t file_size;   ///< Size of the data read.
} File_Response;

/**
 * @brief Reads binary data from a file.
 *
 * This function reads binary data from a specified file path and returns a response structure containing
 * the data and its size.
 *
 * @param[in] file_path The path to the file.
 * @return The response containing the data read from the file.
 */
File_Response read_binary_from_file(char *file_path);

/**
 * @brief Writes a string to a file, with optional appending to an existing file.
 *
 * This function writes the provided string data to a specified file path. If the file already exists,
 * the data can be appended to the existing content.
 *
 * @param[in] data The string data to be written to the file.
 * @param[in] file_path The path to the file for writing.
 * @return Indicates whether the string has been successfully written or not.
 */
bool write_string_to_file(char *data, char *file_path);

/**
 * @brief Removes a file from the file system.
 *
 * This function deletes a file located at the specified file path.
 *
 * @param[in] file_path The path of the file to be removed.
 * @return Indicates whether the file has been successfully removed or not.
 */
bool remove_file(char *file_path);

#endif //_FILE_IO_H_
