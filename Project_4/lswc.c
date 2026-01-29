#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pfd[2];

    if (pipe(pfd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // CHILD: wc -l
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[1]);
        close(pfd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(1);
    } else {
        // PARENT: ls -1a [dir]
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[0]);
        close(pfd[1]);

        if (argc > 1) {
            execlp("ls", "ls", "-1a", argv[1], NULL);
        } else {
            execlp("ls", "ls", "-1a", NULL);
        }

        perror("execlp ls");
        exit(1);
    }
}