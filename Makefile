CXXFLAGS = -g -Wall -Wextra -std=gnu++11 -I/usr/include/lua5.2 $(shell sdl-config --cflags)
LIBS = -llua5.2 -lGL $(shell sdl-config --libs) -lSDL_image -lm

OBJECTS = $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))

.PHONY: all clean

all: game

build:
	mkdir -p $@

game: $(OBJECTS)
	g++ -o game $^ $(LIBS)

build/%.o: src/%.cpp build
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	-rm -Rf build
