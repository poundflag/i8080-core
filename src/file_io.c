#include "file_io.h"
#include <stdio.h>

FILE *open_file_binary_mode(char *file_path) {
    // Open file in binary mode
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", file_path);
        return NULL;
    }
    return file;
}

size_t determine_file_size(FILE *file_input) {
    fseek(file_input, 0, SEEK_END);
    size_t file_size = ftell(file_input);
    fseek(file_input, 0, SEEK_SET);
    return file_size;
}

File_Response get_empty_file_response() {
    File_Response empty_response;
    empty_response.file_data = NULL;
    empty_response.file_size = -1;
    return empty_response;
}

File_Response read_binary_from_file(char *file_path) {
    File_Response file_response;
    FILE *file_input = open_file_binary_mode(file_path);

    if (file_input != NULL) {
        file_response.file_size = determine_file_size(file_input);
        file_response.file_data = (uint8_t *)malloc(file_response.file_size);
        if (file_response.file_data == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file_input);
            return get_empty_file_response();
        }

        size_t bytes_read = fread(file_response.file_data, 1, file_response.file_size, file_input);
        if (bytes_read != file_response.file_size) {
            printf("Failed to read the file: %s\n", file_path);
            free(file_response.file_data);
            fclose(file_input);
            return get_empty_file_response();
        }
        fclose(file_input);
        return file_response;
    }
    return get_empty_file_response();
}

bool write_string_to_file(char *data, char *file_path) {
    FILE *fptr;
    fptr = fopen(file_path, "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return false;
    }
    fprintf(fptr, "%s", data);
    fclose(fptr);
    return true;
}

bool remove_file(char *file_path) {
    File_Response file_response = read_binary_from_file(file_path);
    if (file_response.file_data != NULL) {
        free(file_response.file_data);
        return remove(file_path) == 0;
    } else {
        printf("Error removing file!\n");
        return false;
    }
}