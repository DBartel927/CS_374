CC=gcc
CFLAGS=-Wall -Wextra -Werror -pthread

all: pc

pc: pc.c eventbuf.c
	$(CC) $(CFLAGS) -o pc pc.c eventbuf.c

clean:
	rm -f pc