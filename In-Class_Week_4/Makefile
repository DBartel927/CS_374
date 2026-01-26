TARGETS=pipetest forkpipe printffile

.PHONY: all clean

all: $(TARGETS)

pipetest: pipetest.c
	gcc -Wall -Wextra -o $@ $^

forkpipe: forkpipe.c
	gcc -Wall -Wextra -o $@ $^

printffile: printffile.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)