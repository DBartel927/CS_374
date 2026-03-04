TARGETS=WherePutMutexes WherePutMutexes2 SemaphorePractice SemaphorePractice2 SemaphorePractice3

.PHONY: all clean

all: $(TARGETS)

WherePutMutexes: WherePutMutexes.c
	gcc -Wall -Wextra -o $@ $^

WherePutMutexes2: WherePutMutexes2.c
	gcc -Wall -Wextra -o $@ $^

SemaphorePractice: SemaphorePractice.c
	gcc -Wall -Wextra -o $@ $^

SemaphorePractice2: SemaphorePractice2.c
	gcc -Wall -Wextra -o $@ $^

SemaphorePractice3: SemaphorePractice3.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)