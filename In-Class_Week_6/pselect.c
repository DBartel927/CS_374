#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>

volatile sig_atomic_t sigusr1_flag = 0;

void sigusr1_handler(int sig)
{
    (void)sig;
    sigusr1_flag = 1;
}

int main(void)
{
    struct sigaction sa;
    sigset_t mask, zero;
    fd_set readfds;
    char buffer[128];

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    sa.sa_handler = sigusr1_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    sigemptyset(&zero);

    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    printf("Either enter some text, or...\n");
    printf("go to another window and `kill -USR1 %d`.\n", getpid());

    int result = pselect(
        1,
        &readfds,
        NULL,
        NULL,
        NULL,
        &zero
    );

    if (result == -1) {
        if (errno == EINTR && sigusr1_flag) {
            printf("Got SIGUSR1!\n");
        } else {
            perror("pselect");
        }
    }
    else if (result > 0) {
        if (FD_ISSET(0, &readfds)) {
            int bytes = read(0, buffer, sizeof(buffer)-1);
            if (bytes > 0) {
                buffer[bytes] = '\0';
                printf("You typed: %s\n", buffer);
            }
        }
    }

    return 0;
}