CC=gcc
CLIBS=-lSDLmain -lSDL
CFLAGS=-std=c11 -Wextra -pedantic -pedantic-errors -Wall $(CLIBS)
CDEBUGFLAGS=-pg
CSTABLEFLAGS=-O3

debug: clean
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o corridorsnatch.bin main.c
stable: clean
	$(CC) $(CFLAGS) $(CSTABLEFLAGS) -o corridorsnatch.bin main.c
clean:
	rm -vfr *~ corridorsnatch.bin
