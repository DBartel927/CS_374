#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

volatile sig_atomic_t sigusr1_happened = 0;

void sigusr1_handler(int sig)
{
    (void)sig;
    sigusr1_happened = 1;
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = sigusr1_handler;

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Go to another window and `kill -USR1 %d`\n", getpid());

    while (!sigusr1_happened) {
        sleep(10);
    }

    printf("SIGUSR1 happened!\n");

    return 0;
}