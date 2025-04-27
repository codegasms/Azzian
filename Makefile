# One of PLATFORM_DESKTOP, PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM           ?= PLATFORM_DESKTOP

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= DEBUG

ifeq ($(PLATFORM),PLATFORM_WEB)
    CC = emcc
endif

CFLAGS += -Wall -std=c17 -D_DEFAULT_SOURCE -Wno-missing-braces -DDEBUG -Wall -Wextra -std=c17 -Iinclude -Ilib

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g
    ifeq ($(PLATFORM),PLATFORM_WEB)
        CFLAGS += -sASSERTIONS=1 --profiling
    endif
else
    ifeq ($(PLATFORM),PLATFORM_WEB)
        CFLAGS += -Os
    else
        CFLAGS += -s -Ofast
    endif
endif

ifeq ($(PLATFORM),PLATFORM_WEB)
    # -Os                        # size optimization
    # -O2                        # optimization level 2, if used, also set --memory-init-file 0
    # -sUSE_GLFW=3               # Use glfw3 library (context/input management)
    # -sALLOW_MEMORY_GROWTH=1    # to allow memory resizing -> WARNING: Audio buffers could FAIL!
    # -sTOTAL_MEMORY=16777216    # to specify heap memory size (default = 16MB) (67108864 = 64MB)
    # -sUSE_PTHREADS=1           # multithreading support
    # -sWASM=0                   # disable Web Assembly, emitted by default
    # -sASYNCIFY                 # lets synchronous C/C++ code interact with asynchronous JS
    # -sFORCE_FILESYSTEM=1       # force filesystem to load/save files data
    # -sASSERTIONS=1             # enable runtime checks for common memory allocation errors (-O1 and above turn it off)
    # -sMINIFY_HTML=0            # minify generated html from shell.html
    # --profiling                # include information for code profiling
    # --memory-init-file 0       # to avoid an external memory initialization code file (.mem)
    # --preload-file resources   # specify a resources folder for data compilation
    # --source-map-base          # allow debugging in browser with source map
    # --shell-file shell.html    # define a custom shell .html and output extension
    CFLAGS += -sUSE_GLFW=3 -sTOTAL_MEMORY=512MB --preload-file resources -sMINIFY_HTML=0
	# NOTE: Increase TOTAL_MEMORY memory if OOM

	CFLAGS += -sEXPORTED_RUNTIME_METHODS=HEAPF32

    # Define a custom shell .html and output extension
    CFLAGS += --shell-file ./lib/shell.html
    EXT = .html
endif

# Directories
SRC_DIR := src

ifeq ($(BUILD_MODE),DEBUG)
	BUILD_DIR := build/debug
else
	BUILD_DIR := build/release
endif

# Source files
SOURCE_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJECT_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

# Executable file
TARGET := Azzian

# Linker flags
LDLIBS := -lraylib -lm

# Desired full path to libraylib. No relative paths.
DESTDIR               ?= /usr/local
RAYLIB_INSTALL_PATH   ?= $(DESTDIR)/lib

# raylib header and associated source files
RAYLIB_H_INSTALL_PATH ?= $(DESTDIR)/include

.PHONY: all debug release embed fmt clean

# Build target
all: $(OBJECT_FILES)
	$(CC) $^ -o $(TARGET) $(LDLIBS)

web: $(SOURCE_FILES)
	$(CC) $(CFLAGS) -o $(TARGET).html $^ ./lib/libraylib.a -I$(RAYLIB_H_INSTALL_PATH) -D$(PLATFORM)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -D$(PLATFORM)

embed: embed_assets.py
	python $< $(SRC_DIR)/*.c

fmt:
	clang-format -i src/*.c include/*.h

clean:
	$(RM) -r -- build Azzian Azzian.data Azzian.html Azzian.js Azzian.wasm
