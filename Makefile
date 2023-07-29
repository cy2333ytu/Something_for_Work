# Compiler settings
CC := g++
CFLAGS := -std=c++11 -Wall -Wextra
LDFLAGS := -pthread

# Directories
SRC_DIR := ccy
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))

# Main target
all: $(BIN_DIR)/oj

# Compile individual source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files and create the executable
$(BIN_DIR)/oj: $(OBJS) main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Clean the object files and the executable
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/oj
