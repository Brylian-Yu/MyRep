# Simple Makefile for Linux (g++)
# Directories
BUILD_DIR := build
SRC_DIR := src
INCLUDE_DIR := include
LIB_DIR := lib

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -I$(INCLUDE_DIR) -O2 -Wall -Wextra
LDFLAGS :=
LDLIBS :=

# Target
TARGET := $(BUILD_DIR)/app

# Sources and objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
MAIN_FILE := main.cpp

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES)) \
             $(BUILD_DIR)/main.o

.PHONY: all clean run

all: $(TARGET)

# Create build directory (POSIX)
$(BUILD_DIR):
	@mkdir -p "$(BUILD_DIR)"

# Object rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(MAIN_FILE) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link
$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Run
run: all
	./$(TARGET)

# Clean (POSIX)
clean:
	rm -rf "$(BUILD_DIR)"
