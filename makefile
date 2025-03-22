CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -Iinclude

SRC = src/main.cpp src/tinyxml/tinyxml2.cpp

BUILD = build

OBJ = $(patsubst src/%.cpp, $(BUILD)/%.o, $(SRC))

TARGET = raytracer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) $(TARGET)
