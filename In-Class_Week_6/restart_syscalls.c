#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void sigusr1_handler(int sig)
{
    (void)sig;
    write(1, "SIGUSR1 handled\n", 16);
}

int main(void)
{
    char buf[128];
    struct sigaction sa;

    sa.sa_handler = sigusr1_handler;

    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Reading from the keyboard. But don't type anything.\n");
    printf("Go to another window and run:\n");
    printf("kill -USR1 %d\n", getpid());

    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));

    if (n == -1) {
        perror("read");
    } else {
        printf("Read returned %zd bytes\n", n);
    }

    return 0;
}