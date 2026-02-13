Did the program exit immediately when you hit ^C, or did it keep running to the end?

Yes, the program was exited because of the wait value.

What was the return value from sleep()?

Sleep returns the number of seconds left if/when interrupted by the signal.

What was different?

Without SA_RESTART, the signal interrupts the program, while with it the program (in this case read()) is restarted with no interruption. In other words, without it the read fails, while with it the read automatically resumes.

Why have sleep() in the loop? Why not just continually check to see if the flag is set?

We make the program sleep because if the while loop were constantly active, it would quickly fully occupy the CPU and waste resources. Calling sleep prevents CPU "spinning".

Research: what does the volatile keyword do? Speculate on why it is necessary to use with sig_atomic_t.

Volatile is a way of telling the compiler that this variable can change at any time, even beyond normal program flow. sig_atomic_t guarantees the read/write, preventing an infinite loop.

When you kill -USR1 several times, only one signal seems to come through and get handled. Why is that?

Unix signals are not queued, so when we send multiple signals, only one pending instance is stored.