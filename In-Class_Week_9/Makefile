TARGETS=WherePutMutexes WherePutMutexes2

.PHONY: all clean

all: $(TARGETS)

WherePutMutexes: WherePutMutexes.c
	gcc -Wall -Wextra -o $@ $^

WherePutMutexes2: WherePutMutexes2.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)