// Write a program forkpipe.c that does the following:

// Create a pipe
// fork() a child process
// The child process should:
// Close the read end of the pipe
// Send Hello, parent!\n into the write end of the pipe
// Exit
// The parent process should:
// Close the write end of the pipe
// Read from the read end of the pipe
// Write to stdout the results of the read
// Wait for the child process to exit

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    int pfds[2];

    pipe(pfds);

    int read_fd = pfds[0];
    int write_fd = pfds[1];

    pid_t pid = fork();

    char buf[128];

    if (pid == 0) {
        close(read_fd);
        write(write_fd, "Hello, parent!\n", 15);
        exit(0);
    } else {
        close(write_fd);
        int count = read(read_fd, buf, 128);
        write(1, buf, count);
        wait(NULL);
    }
}