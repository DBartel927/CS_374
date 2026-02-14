#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>

#define INITIAL_SPEED 0
#define STDIN_FD 0
#define BUFFER_SIZE 128

volatile sig_atomic_t sigusr1_flag = 0;
volatile sig_atomic_t sigusr2_flag = 0;

void sigusr1_handler(int sig)
{
    (void)sig;
    sigusr1_flag = 1;
}

void sigusr2_handler(int sig)
{
    (void)sig;
    sigusr2_flag = 1;
}

void increase_speed(int *speed)
{
    (*speed)++;
    printf("increase speed to: %d\n", *speed);
    fflush(stdout);
}

void decrease_speed(int *speed)
{
    if (*speed > 0) {
        (*speed)--;
    }
    printf("decrease speed to: %d\n", *speed);
    fflush(stdout);
}

int main(void)
{
    struct sigaction sa_usr1, sa_usr2;
    sigset_t block_mask, empty_mask;
    int speed = INITIAL_SPEED;
    char buffer[BUFFER_SIZE];

    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGUSR1);
    sigaddset(&block_mask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &block_mask, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    sa_usr1.sa_handler = sigusr1_handler;
    sa_usr1.sa_flags = 0;
    sigemptyset(&sa_usr1.sa_mask);

    if (sigaction(SIGUSR1, &sa_usr1, NULL) == -1) {
        perror("sigaction SIGUSR1");
        exit(EXIT_FAILURE);
    }

    sa_usr2.sa_handler = sigusr2_handler;
    sa_usr2.sa_flags = 0;
    sigemptyset(&sa_usr2.sa_mask);

    if (sigaction(SIGUSR2, &sa_usr2, NULL) == -1) {
        perror("sigaction SIGUSR2");
        exit(EXIT_FAILURE);
    }

    printf("PID=%d\n", getpid());
    fflush(stdout);

    sigemptyset(&empty_mask);

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FD, &readfds);

        int result = pselect(
            STDIN_FD + 1,
            &readfds,
            NULL,
            NULL,
            NULL,
            &empty_mask
        );

        if (result == -1) {
            if (errno == EINTR) {
                if (sigusr1_flag) {
                    sigusr1_flag = 0;
                    decrease_speed(&speed);
                }
                if (sigusr2_flag) {
                    sigusr2_flag = 0;
                    increase_speed(&speed);
                }
                continue;
            } else {
                perror("pselect");
                exit(EXIT_FAILURE);
            }
        }

        if (FD_ISSET(STDIN_FD, &readfds)) {
            ssize_t bytes = read(STDIN_FD, buffer, BUFFER_SIZE);

            if (bytes > 0) {
                for (ssize_t i = 0; i < bytes; i++) {
                    char c = buffer[i];

                    if (c == '+') {
                        increase_speed(&speed);
                    }
                    else if (c == '-') {
                        decrease_speed(&speed);
                    }
                    else if (c == 'q') {
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}