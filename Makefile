CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o corridorsnatch main.c
stable:clean
	$(CC) $(CFLAGS) -o corridorsnatch main.c
clean:
	rm -vfr *~ corridorsnatch
