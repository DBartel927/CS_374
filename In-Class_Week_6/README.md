Did the program exit immediately when you hit ^C, or did it keep running to the end?

Yes, the program was exited because of the wait value.

What was the return value from sleep()?

Sleep returns the number of seconds left if/when interrupted by the signal.

What was different?

Without SA_RESTART, the signal interrupts the program, while with it the program (in this case read()) is restarted with no interruption. In other words, without it the read fails, while with it the read automatically resumes.