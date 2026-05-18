# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra

# Directories
SRC_DIR := Src
BUILD_DIR := Build

# Output binary name
TARGET := pixlhide

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile source files into build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build and run
run: all
	./$(TARGET)

# Remove build files and executable
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all run clean