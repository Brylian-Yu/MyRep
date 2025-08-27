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

# Sources and objects
SRCS := main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

INCLUDES := -I$(INCLUDE_DIR)

.PHONY: all clean run

all: $(TARGET)

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Compilation rules
$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run the application
run: all
	./$(TARGET)

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)
