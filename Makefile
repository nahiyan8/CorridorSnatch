CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -o corridorsnatch.bin main.c
stable:clean
	$(CC) $(CFLAGS) -o corridorsnatch.bin main.c
clean:
	rm -vfr *~ corridorsnatch
