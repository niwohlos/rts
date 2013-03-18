CXXFLAGS = -g -Wall -Wextra -std=gnu++11 -I/usr/include/lua5.2 $(shell sdl-config --cflags)
LIBS = -llua5.2 -lGL $(shell sdl-config --libs) -lSDL_image

.PHONY: all clean

all:
	mkdir -p build
	make game

game: $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))
	g++ -o game $^ $(LIBS)

build/%.o: src/%.cpp
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	-rm -Rf build
