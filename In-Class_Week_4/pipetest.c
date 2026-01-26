// Write a program pipetest.c that does this:

// Create a pipe
// Write the string Hello\n into the write end of the pipe
// Read it out of the read end of the pipe
// Write the result to stdout
// You can create a pipe with the pipe() syscall:

// int pfds[2];  // pipe file descriptors
//               // 0 is the read end, 1 is the write end

// pipe(pfds);   // create the pipe
// Use the syscalls read() and write() to do the rest of the I/O.

// Hint: you can get the number of bytes read from the pipe from the return value of read(). You can use this when write()ing them to stdout.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int pfds[2];

    pipe(pfds);

    int read_fd = pfds[0];
    int write_fd = pfds[1];

    char buf[128];

    write(write_fd, "Hello\n", 6);
    int count = read(read_fd, buf, 128);

    write(1, buf, count);
}