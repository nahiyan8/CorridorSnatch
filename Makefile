CC=gcc
CLIBS=-lSDLmain -lSDL
CFLAGS=-std=c11 -Wextra -pedantic -pedantic-errors -Wall $(CLIBS)
CDEBUGFLAGS=-pg
CSTABLEFLAGS=-O3

debug: clean
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o bin/corridorsnatch.bin src/main.c
stable: clean
	$(CC) $(CFLAGS) $(CSTABLEFLAGS) -o bin/corridorsnatch.bin src/main.c
clean:
	rm -vfr *~ corridorsnatch.bin
