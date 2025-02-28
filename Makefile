CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
TARGET = lvl1

# Automatically find all source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Include header files
INCLUDES = -I$(INCLUDE_DIR)

# Link the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean
