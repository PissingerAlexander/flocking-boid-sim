# Complier and flags
GXX = g++
GXXFLAGS = -Wall

# Libraries to link
LIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# Source and output
BUILD_DIR = build
TARGET_NAME = out.a
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
