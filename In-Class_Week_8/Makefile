TARGETS=mutexes_1 mutexes_2

.PHONY: all clean

all: $(TARGETS)

mutexes_1: mutexes_1.c
	gcc -Wall -Wextra -o $@ $^

mutexes_2: mutexes_2.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)