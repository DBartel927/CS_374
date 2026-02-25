TARGETS=mutexes_1 mutexes_2 deadlock llist

.PHONY: all clean

all: $(TARGETS)

mutexes_1: mutexes_1.c
	gcc -Wall -Wextra -o $@ $^

mutexes_2: mutexes_2.c
	gcc -Wall -Wextra -o $@ $^

deadlock: deadlock.c
	gcc -Wall -Wextra -o $@ $^

llist: llist.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)