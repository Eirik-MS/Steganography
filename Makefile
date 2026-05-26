.DEFAULT_GOAL := help

# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -g -O0
CFLAGS_RELEASE := -Wall -Wextra -O2
LDFLAGS :=

# Sanitizer flags (used by *_san targets)
SAN_FLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

# Directories
SRC_DIR   := Src
BUILD_DIR := Build

# Output binary names
TARGET     := pixlhide
TARGET_SAN := $(BUILD_DIR)/pixlhide_san

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS     := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
OBJS_SAN := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.san.o,$(SRCS))

# Default test parameters (override on command line: make memtest ARGS="-r ...")
ARGS ?= -d -secret Evassd.bmp -k 2 -n 3 -dir Images
ARGS2 ?= -r -secret Evassd.bmp -k 2 -n 3 -dir Images


# Default target
all: $(TARGET) ## Build the program with debug symbols and verbose output (default)

# --- Build folder and other targets -------------------------------------

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_SAN): $(OBJS_SAN)
	$(CC) $(CFLAGS) $(SAN_FLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.san.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SAN_FLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# --- Release target ------------------------------------------------
release: CFLAGS := $(CFLAGS_RELEASE)
release: $(TARGET) ## Build with optimizations (no debug symbols, no verbose) Do make clean before this to remove old debug builds.
	@echo "Release build complete."

# --- Run targets -----------------------------------------------------------
run: all ## Build and run the program with default arguments
	./$(TARGET) $(ARGS)

santest: $(TARGET_SAN) ## Quick sanitizer run (fast, catches most memory + UB issues)
	@echo "=== Running with AddressSanitizer + UBSan ==="
	./$(TARGET_SAN) $(ARGS)

memtest: $(TARGET) ## Run with Valgrind to test for memmory leaks (slower, but very thorough)
	@command -v valgrind >/dev/null 2>&1 || { \
		echo "Error: valgrind not installed. Try: sudo apt install valgrind"; \
		exit 1; }
	@echo "=== Running under Valgrind ==="
	valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         --error-exitcode=1 \
	         ./$(TARGET) $(ARGS)

roundtrip: all ## Distribute then recover, to verify the round-trip works
	./$(TARGET) -d -secret Evassd.bmp -k 2 -n 3 -dir Images
	./$(TARGET) -r -secret recovered.bmp -k 2 -n 3 -dir Images
	@echo "=== Comparing original to recovered ==="
	cmp Images/Evassd.bmp recovered.bmp && echo "MATCH" || echo "DIFFER"

# --- Help -----------------------------------------------------------------

help: ## Show this help message
	@echo "Available targets:"
	@echo ""
	@awk 'BEGIN {FS = ":.*?## "} \
		/^[a-zA-Z_-]+:.*?## / { printf "  \033[36m%-12s\033[0m %s\n", $$1, $$2 }' \
		$(MAKEFILE_LIST)
	@echo ""
	@echo "Override test arguments with ARGS=\"...\""
	@echo "  Example: make memtest ARGS=\"-r -secret out.bmp -k 2 -dir Images\""

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET_SAN)

.PHONY: all run santest memtest roundtrip build help clean