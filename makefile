CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -Iinclude

SRC = \
      src/tinyxml/tinyxml2.cpp \
	  src/AmbientLight.cpp \
	  src/Camera.cpp \
	  src/Color.cpp \
	  src/Face.cpp \
	  src/Intensity.cpp \
	  src/Light.cpp \
	  src/Material.cpp \
	  src/Math.cpp \
	  src/Object.cpp \
	  src/Parser.cpp \
	  src/Plane.cpp \
	  src/PointLight.cpp \
	  src/Scene.cpp \
	  src/Vector.cpp \
	  src/main.cpp 

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
