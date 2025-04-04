TARGET = run
SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build
INC_DIR = include

CXXFLAGS = -Wall -Wextra -I$(INC_DIR) -mavx -march=native -flto
LDFLAGS = -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system

# Test --------------------------------------
TEST ?= 0

ifeq ($(TEST), 1)
	CXXFLAGS += -DTEST
endif
#--------------------------------------------

# Compiler ----------------------------------
CXX ?= g++

ifeq ($(CXX), gcc)
	CXXFLAGS += -DGCC 
else ifeq ($(CXX), g++)
	CXXFLAGS += -DGPP
else ifeq ($(CXX), clang)
	CXXFLAGS += -DCLANG 
else
	CXXFLAGS += -DGPP
endif
#--------------------------------------------

# Optimizations -----------------------------
OPT ?= 

ifeq ($(OPT), -O1)
	CXXFLAGS += -O1
	CXXFLAGS += -DO1
else ifeq ($(OPT), -O2)
	CXXFLAGS += -O2
	CXXFLAGS += -DO2
else ifeq ($(OPT), -O3)
	CXXFLAGS += -O3
	CXXFLAGS += -DO3
endif
#--------------------------------------------

# Render mode -------------------------------
RENDER_MODE ?= DEFAULT_RENDER

ifeq ($(RENDER_MODE), DEFAULT_RENDER)
	CXXFLAGS += -DDEFAULT_RENDER
else ifeq ($(RENDER_MODE), VECTORIZED_RENDER)
	CXXFLAGS += -DVECTORIZED_RENDER
else ifeq ($(RENDER_MODE), ARRAYED_RENDER)
	CXXFLAGS += -DARRAYED_RENDER
else
	CXXFLAGS += -DDEFAULT_RENDER
endif
#--------------------------------------------

# Graphics mode -----------------------------
GRAPHICS_MODE ?= 1

ifeq ($(GRAPHICS_MODE), 0)
	CXXFLAGS += -DNO_GRAPHICS
else
	CXXFLAGS += -DGRAPHICS
endif
# -------------------------------------------

SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/defaultRender.cpp $(SRC_DIR)/vectorizedRender.cpp $(SRC_DIR)/arrayedRender.cpp $(SRC_DIR)/benchmark.cpp
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

$(BIN_DIR)/$(TARGET): $(OBJECTS) 
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
# g++ -Iinclude -S -fverbose-asm -O2 ./src/defaultRender.cpp -o output.s

.PHONY: clean run

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

run: $(BIN_DIR)/$(TARGET)
	./$<
