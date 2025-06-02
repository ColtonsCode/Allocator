# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -MMD -MP

# Target executable
TARGET = allocator_test

BUILD_DIR = build

# Source files and object files
SRCS = main.c cc_allocate.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Linking the executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Ensure build directory exists and compile each .c into build/*.o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Include dependency files
-include $(DEPS)

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the program
run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

