# Compiler
# CC := gcc

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Object files
DEBUG_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/debug/%.o,$(SRCS))
RELEASE_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/release/%.o,$(SRCS))

# Executable file
TARGET := Azzian

# Compiler flags
DEBUG_CFLAGS := -ggdb -DDEBUG -Wall -Wextra -std=c17 -Iinclude -isystemlib
RELEASE_CFLAGS := -Ofast -DNDEBUG -Wall -Wextra -std=c17 -Iinclude -isystemlib

# Linker flags
LDFLAGS := -lraylib -lm

.PHONY: all debug release embed fmt clean

# Build target
all: debug

debug: $(DEBUG_OBJS)
	$(CC) $^ -o $(TARGET) $(LDFLAGS)

release: $(RELEASE_OBJS)
	$(CC) $^ -o $(TARGET) $(LDFLAGS)

# Compile source files
$(BUILD_DIR)/debug/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/debug
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@

$(BUILD_DIR)/release/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/release
	$(CC) $(RELEASE_CFLAGS) -c $< -o $@

embed: embed_assets.py
	python $< $(SRC_DIR)/*.c

fmt:
	clang-format -i src/*.c include/*.h

clean:
	$(RM) -r -- $(BUILD_DIR) $(TARGET)
