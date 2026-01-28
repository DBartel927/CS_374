TARGETS=pipetest forkpipe printffile producer consumer producer4.5 consumer4.5

.PHONY: all clean

all: $(TARGETS)

pipetest: pipetest.c
	gcc -Wall -Wextra -o $@ $^

forkpipe: forkpipe.c
	gcc -Wall -Wextra -o $@ $^

printffile: printffile.c
	gcc -Wall -Wextra -o $@ $^

producer: producer.c
	gcc -Wall -Wextra -o $@ $^

consumer: consumer.c
	gcc -Wall -Wextra -o $@ $^

producer4.5: producer4.5.c
	gcc -Wall -Wextra -o $@ $^

consumer4.5: consumer4.5.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)