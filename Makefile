# Compiler
CC := gcc

# Directories
SRC_DIR := screens
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

# Executable file
TARGET := Azzian

# Compiler flags
CFLAGS := -Wall -Wextra -ggdb -std=c99 -Iheaders/

# Linker flags
LDFLAGS := -lraylib

# Build target
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)
	rm -f Azzian