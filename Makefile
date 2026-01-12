TARGETS=recordfile

.PHONY: all clean

all: $(TARGETS)

recordfile: recordfile.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)