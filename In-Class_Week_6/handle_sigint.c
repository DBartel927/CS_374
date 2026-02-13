#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "Got SIGINT!\n", 12);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Program will exit in 10 seconds. Hit ^C!\n");

    unsigned int remaining = sleep(10);

    printf("sleep() returned: %u\n", remaining);

    return 0;
}