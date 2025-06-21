CXX = g++
CXXFLAGS = -std=c++17 $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_ttf)
LDFLAGS = $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_ttf)

TARGET = jeuuuuu
SOURCES = $(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

makerun: $(TARGET)
	./$(TARGET)

.PHONY: all clean makerun
