CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SDL_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image)
SDL_LIBS := $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image)
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, build/%.o, $(SRCS))
TARGET := bin/arme_fatal

all: $(TARGET)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -Iinclude -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(OBJS) $(SDL_LIBS) -o $@

clean:
	rm -rf build $(TARGET)

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run
