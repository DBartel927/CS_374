TARGETS=ignore_sigint handle_sigint restart_syscalls sig_atomic_t blocking_signals pselect

.PHONY: all clean

all: $(TARGETS)

ignore_sigint: ignore_sigint.c
	gcc -Wall -Wextra -o $@ $^

handle_sigint: handle_sigint.c
	gcc -Wall -Wextra -o $@ $^

restart_syscalls: restart_syscalls.c
	gcc -Wall -Wextra -o $@ $^

sig_atomic_t: sig_atomic_t.c
	gcc -Wall -Wextra -o $@ $^

blocking_signals: blocking_signals.c
	gcc -Wall -Wextra -o $@ $^

pselect: pselect.c
	gcc -Wall -Wextra -o $@ $^

clean:
	rm -f $(TARGETS)