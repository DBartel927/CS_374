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
    char buffer[128];
    struct sigaction sa;
    sigset_t mask, oldmask;

    sa.sa_handler = sigusr1_handler;

    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    printf("SIGUSR1 is blocked.\n");
    printf("Reading from the keyboard. But don't type anything.\n");
    printf("Go to another window and `kill -USR1 %d` several times.\n", getpid());
    printf("Then press RETURN to continue.\n");

    read(0, buffer, sizeof(buffer));

    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    printf("Signal unblocked.\n");

    return 0;
}