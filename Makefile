TARGETS=recordfile getsize

.PHONY: all clean

all: $(TARGETS)

recordfile: recordfile.c
	gcc -Wall -Wextra -o $@ $^

getsize: getsize.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)