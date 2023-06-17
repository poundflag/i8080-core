CC = gcc
ARGS = -Wall -Wextra
TEST_ARGS = $(ARGS) -lcheck

SRC_DIR = src
TEST_DIR = test
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/**/*.c) $(filter-out src/main.c, $(wildcard $(SRC_DIR)/*.c))
MAIN_FILE = $(SRC_DIR)/main.c
HEADER_FILES = $(wildcard $(SRC_DIR)/**/*.h) $(wildcard $(SRC_DIR)/*h)
TEST_FILES = $(wildcard $(TEST_DIR)/**/*.c) $(wildcard $(TEST_DIR)/*c)

EXECUTABLE = $(BIN_DIR)/i8080-core
TEST_EXECUTABLE = $(BIN_DIR)/test-i8080-core

# Setting the debug flag at compilation time for gcc if DEBUG=1
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	ARGS += -g
endif

.PHONY: all test

all: $(EXECUTABLE)
	$(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(ARGS) $(MAIN_FILE) $(SRC_FILES) $(HEADER_FILES) -o $(EXECUTABLE)

test: $(TEST_EXECUTABLE)
	$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(SRC_FILES) $(HEADER_FILES) $(TEST_FILES)
	$(CC) $(TEST_FILES) $(SRC_FILES) $(HEADER_FILES) $(TEST_ARGS) -o $(TEST_EXECUTABLE)