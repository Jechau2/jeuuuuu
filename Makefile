CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SDL_CFLAGS := $(shell pkg-config --cflags sdl2 SDL2_ttf)
SDL_LIBS := $(shell pkg-config --libs sdl2 SDL2_ttf)
MINER_SRCS := src/mine.cpp src/miner_main.cpp

OBJS := $(patsubst src/%.cpp, build/%.o, $(SRCS))
MINER_OBJS := $(patsubst src/%.cpp, build/%.o, $(MINER_SRCS))
TARGET := bin/arme_fatal
MINER_TARGET := bin/mine_game

all: $(TARGET)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -Iinclude -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(OBJS) $(SDL_LIBS) -o $@

$(MINER_TARGET): $(MINER_OBJS)
	@mkdir -p bin
	$(CXX) $(MINER_OBJS) -o $@

clean:
	rm -rf build $(TARGET) $(MINER_TARGET)

run: $(TARGET)
	$(TARGET)

miner_run: $(MINER_TARGET)
	$(MINER_TARGET)
.PHONY: all clean run miner_run
