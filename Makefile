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
LDFLAGS := -lraylib -lm

# Build target
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

fmt:
	clang-format -i screens/*.c headers/*.h

clean:
	$(RM) -r -- $(BIN_DIR)/*.o $(TARGET)
	$(RM) -- Azzian
