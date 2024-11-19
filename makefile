CC = gcc
CFLAGS = -Wall -Wextra -I./include
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/utils.c \
          $(SRC_DIR)/help.c \
          $(SRC_DIR)/crtdir.c \
          $(SRC_DIR)/crtfile.c \
          $(SRC_DIR)/delete_file.c \
          $(SRC_DIR)/list.c \
          $(SRC_DIR)/read_file.c \
          $(SRC_DIR)/mod.c

OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

EXECUTABLES = $(BIN_DIR)/minishell \
              $(BIN_DIR)/help \
              $(BIN_DIR)/crtdir \
              $(BIN_DIR)/crtfile \
              $(BIN_DIR)/delete_file \
              $(BIN_DIR)/list \
              $(BIN_DIR)/read_file \
              $(BIN_DIR)/mod

all: $(EXECUTABLES)

$(BIN_DIR)/minishell: $(OBJ_DIR)/main.o $(OBJ_DIR)/utils.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJ_DIR)/utils.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

#Limpiar
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

#Limpieza y reconstrucción
rebuild: clean all

#Ejecutar
run: $(BIN_DIR)/minishell
	cd $(BIN_DIR) && ./minishell

.PHONY: all clean rebuild run
