# Simple Makefile for Linux (g++)

# Directories
BUILD_DIR := build
SRC_DIR := src
INCLUDE_DIR := include

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -I. -O2 -Wall -Wextra -Werror

# Target
TARGET := $(BUILD_DIR)/app

# Find all source files
SRCS := $(wildcard *.cpp) $(shell find $(SRC_DIR) -name '*.cpp')

# Generate object file paths by replacing src/ with build/ and keeping subdirectories
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SRCS)))
OBJS += $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(filter-out $(SRC_DIR)/%,$(SRCS)))

# Add include paths
CXXFLAGS += -I$(INCLUDE_DIR)

.PHONY: all clean run

all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Generic rule to compile source files into object files
# This handles both root .cpp files and files in src/
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the application
run: all
	./$(TARGET)

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)
