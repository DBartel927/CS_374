CC=gcc
CFLAGS=-Wall -Wextra -Werror -pthread

all: grayscaler

grayscaler: grayscaler.c ppm.c
	$(CC) $(CFLAGS) -o grayscaler grayscaler.c ppm.c

clean:
	rm -f grayscaler