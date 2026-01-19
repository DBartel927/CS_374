CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = filescanner

all: $(TARGET)

$(TARGET): filescanner.o
	$(CC) $(CFLAGS) -o $(TARGET) filescanner.o

filescanner.o: filescanner.c
	$(CC) $(CFLAGS) -c filescanner.c

clean:
	rm -f *.o $(TARGET)