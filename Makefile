CC=gcc
CFLAGS=-m64 -std=c11 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -pg
LDFLAGS=-lSDLmain -lSDL

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))

all: $(OBJ)
	mkdir -p bin/
	$(CC) $(LDFLAGS) $^ -o bin/corridorsnatch.bin

obj/%.o: src/%.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -c $^ -o $@

test:
	echo -e "\nCC=$(CC)\nLDFLAGS=$(LDFLAGS)\nCFLAGS=$(CFLAGS)\nSRC=$(SRC)\nOBJ=$(OBJ)\n"

clean:
	rm -vfr bin/* obj/*
