CC=g++
CPPFLAGS=-m64 -std=c++11 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wno-switch -Werror -g -pg
LDFLAGS=-lSDLmain -lSDL

SRC=$(wildcard src/*.cpp)
OBJ=$(patsubst src/%.cpp,obj/%.o,$(wildcard src/*.cpp))

all: $(OBJ)
	mkdir -p bin/
	$(CC) $(LDFLAGS) $(OBJ) -o bin/corridorsnatch.bin

obj/%.o: src/%.cpp
	mkdir -p obj/
	$(CC) $(CPPFLAGS) -c $< -o $@

test:
	echo -e "\nCC=$(CC)\nLDFLAGS=$(LDFLAGS)\nCFLAGS=$(CFLAGS)\nSRC=$(SRC)\nOBJ=$(OBJ)\n"

clean:
	rm -vfr bin/* obj/*
