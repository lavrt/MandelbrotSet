# ======================
# Project Settings
# ======================
CXX := g++
TARGET := run
SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build
INC_DIR := include

# ======================
# Compilation flags
# ======================
# -march=native -flto -O2/-O3
CXXFLAGS := -Wall -Wextra -I$(INC_DIR) -mavx -O3
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# ======================
# Search for source files
# ======================
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# ======================
# Basic rules
# ======================
$(BIN_DIR)/$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# ======================
# Creating directories
# ======================
$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

# ======================
# Auxiliary commands
# ======================
.PHONY: clean run

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)