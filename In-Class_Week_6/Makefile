TARGETS=ignore_sigint handle_sigint restart_syscalls

.PHONY: all clean

all: $(TARGETS)

ignore_sigint: ignore_sigint.c
	gcc -Wall -Wextra -o $@ $^

handle_sigint: handle_sigint.c
	gcc -Wall -Wextra -o $@ $^

restart_syscalls: restart_syscalls.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)