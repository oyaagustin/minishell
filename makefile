# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -I./include

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Source files (excluding utils.c)
SRC_FILES := $(filter-out $(SRC_DIR)/utils.c,$(wildcard $(SRC_DIR)/*.c))

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
UTILS_OBJ := $(OBJ_DIR)/utils.o

# Executables
EXECUTABLES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC_FILES))

# Default target
all: $(EXECUTABLES)

# Rule to create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create executables
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(UTILS_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild everything
re: clean all

# Run the main program
run: $(BIN_DIR)/main
	cd $(BIN_DIR) && ./main

.PHONY: all clean re run
