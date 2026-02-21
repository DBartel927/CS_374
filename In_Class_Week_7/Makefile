TARGETS=threads threads2 launch3 sharedarray

.PHONY: all clean

all: $(TARGETS)

threads: threads.c
	gcc -Wall -Wextra -o $@ $^

threads2: threads2.c
	gcc -Wall -Wextra -o $@ $^

launch3: launch3.c
	gcc -Wall -Wextra -o $@ $^

sharedarray: sharedarray.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)