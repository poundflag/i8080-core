CC = gcc
ARGS = -Wall -Wextra -fPIC
TEST_ARGS = $(ARGS) -lcheck

# Folder Variables
SRC_DIR = src
BIN_DIR = bin
BIN_OBJ_DIR = $(BIN_DIR)/obj

# Project files that will be used in the build process
HEADERS = $(wildcard $(SRC_DIR)/*.h $(SRC_DIR)/**/*.h)
HEADERS_NO_EXT = $(basename $(HEADERS))
OBJECT_FILES = $(addprefix $(BIN_OBJ_DIR)/, $(addsuffix .o, $(HEADERS_NO_EXT)))

.PHONY: all bin lib clean

all: bin lib

bin: $(OBJECT_FILES)
	@$(CC) $(ARGS) $(OBJECT_FILES) src/main.c -o $(BIN_DIR)/i8080-core
	@echo Created binary executable

lib: $(OBJECT_FILES)
	@$(CC) $(ARGS) $(OBJECT_FILES) -shared -o $(BIN_DIR)/i8080-core.so 
	@echo Created shared library

$(BIN_OBJ_DIR)/%.o: %.c %.h
	@mkdir -p $(dir $@)
	$(CC) $(ARGS) -c $< -o $@

clean:
	@rm -rf $(BIN_OBJ_DIR)