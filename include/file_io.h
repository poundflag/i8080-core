#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef _FILE_IO_H_
#define _FILE_IO_H_

typedef struct {
    uint8_t *file_data;
    size_t file_size;
} File_Response;

File_Response read_binary_from_file(char *file_path);
bool write_string_to_file(char *data, char *file_path);
bool remove_file(char *file_path);

#endif //_FILE_IO_H_