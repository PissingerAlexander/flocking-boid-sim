# Complier and flags
GXX = g++
GXXFLAGS = -Wall -g

# Libraries to link
LIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# Source and output
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

TARGET = $(BUILD_DIR)/a.out

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(GXX) $(OBJECTS) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(GXX) $(GXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

debug:
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Target: $(TARGET)"

.PHONY: all clean rebuild run debug
