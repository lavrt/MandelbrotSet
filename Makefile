CXX = g++
TARGET = run
SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build
INC_DIR = include

CXXFLAGS = -Wall -Wextra -I$(INC_DIR) -mavx -march=native -flto -O2
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/defaultRender.cpp $(SRC_DIR)/vectorizedRender.cpp $(SRC_DIR)/arrayedRender.cpp
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

run: $(BIN_DIR)/$(TARGET)
	./$<
