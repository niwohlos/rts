CXXFLAGS = -g -Wall -Wextra -std=gnu++11

.PHONY: all clean

all:
	mkdir -p build
	make game

game: $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))
	g++ -o game $<

build/%.o: src/%.cpp
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	-rm -Rf build
