CC = gcc
ARGS = -Wall -Wextra -fPIC
TEST_ARGS = $(ARGS) -lcheck

# Folder Variables
SRC_DIR = src
TEST_DIR = test
BIN_DIR = bin
BIN_OBJ_DIR = $(BIN_DIR)/obj

# Project files that will be used in the build process
HEADERS = $(wildcard $(SRC_DIR)/*.h $(SRC_DIR)/**/*.h)
HEADERS_NO_EXT = $(basename $(HEADERS))
OBJECT_FILES = $(addprefix $(BIN_OBJ_DIR)/, $(addsuffix .o, $(HEADERS_NO_EXT)))

# Files that will be used for the test build
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c $(TEST_DIR)/**/*.c)
TEST_SOURCES_NO_EXT = $(basename $(TEST_SOURCES))
TEST_OBJECT_FILES =$(addprefix $(BIN_OBJ_DIR)/, $(addsuffix .o, $(TEST_SOURCES_NO_EXT)))

.PHONY: all bin lib test clean

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

test: $(TEST_OBJECT_FILES) $(OBJECT_FILES)
	@$(CC) $(TEST_ARGS) $(TEST_OBJECT_FILES) $(OBJECT_FILES) -o $(BIN_DIR)/i8080-core-test
	@echo Created test executable
	bin/i8080-core-test

$(BIN_OBJ_DIR)/test/%.o: test/%.c
	@mkdir -p $(dir $@)
	$(CC) $(TEST_ARGS) -c $< -o $@

clean:
	@rm -rf $(BIN_OBJ_DIR)