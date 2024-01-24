# Compiler and flags
CC = gcc -Wall 

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)


# Executable name
TARGET = bin/social_network

# Main target
all: bin/social_network


$(TARGET): $(SRCS) $(BUILD_DIR)
	$(CC) code/*.c -o $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $@

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $@

# Clean rule to remove generated files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony target to avoid conflicts with files named clean
.PHONY: all clean
