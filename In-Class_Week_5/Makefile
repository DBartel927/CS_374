TARGETS=mmap_read mmap_write

.PHONY: all clean

all: $(TARGETS)

mmap_read: mmap_read.c
	gcc -Wall -Wextra -o $@ $^

mmap_write: mmap_write.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)