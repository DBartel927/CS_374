TARGETS=mmap_read mmap_write locks mmap_flat_lock

.PHONY: all clean

all: $(TARGETS)

mmap_read: mmap_read.c
	gcc -Wall -Wextra -o $@ $^

mmap_write: mmap_write.c
	gcc -Wall -Wextra -o $@ $^

locks: locks.c
	gcc -Wall -Wextra -o $@ $^

mmap_flat_lock: mmap_flat_lock.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)