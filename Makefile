# Compiler and flags
CC = g++
CFLAGS = -Wall 

# Raylib libraries and options
RAYLIB_FLAGS = -lraylib

# Paths and files
SRC_DIR = src
OBJ_DIR = obj
TARGET = game

# Find all .c files in the src directory and corresponding .o files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(RAYLIB_FLAGS)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Ensure the obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up compiled files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean

