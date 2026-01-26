// Write a program called printffile that will send all output from printf() into a file.

// Do not use fprintf()!

// That is, the code will say:

// printf("Hello, world\nThis is a test!\n");
// and that output will go to a file instead of the screen.

// Steps:

// open() file output.txt for creation and truncation
// Use dup2() to dup the file's file descriptor into stdout's file descriptor (i.e. 1)
// Run the printf()
// Flush the output with fflush(stdout)
// close() the file
// Opening files
// You can open a file like this:

// int fd = open("output.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);
// The second argument is the bitwise-OR of a bunch of flags. The ones used here are:

// O_CREAT: create the file if it doesn't exist
// O_TRUNC: truncate the file to 0 bytes if it does exist
// O_WRONLY: open the file for write only
// The third argument are the permissions for when the file is created. This must be set, even if the compiler doesn't complain if you don't.

// The permission is usually specified in octal (leading 0 on the number).

// Here are some common permissions:

// 0644: rw-r--r--: You get rw, group gets r, other gets r.
// 0755: rwxr-xr-x: You get rwx, group gets rx, other gets rx
// 0600: rw-------: You get rw, no one else gets anything
// 0700: rwx------: You get rwx, no one else gets anything
// If you write 0644 in binary, you get this: 110100100. See how the Unix permissions work?

// Also, you'll want to test for errors in the open(), which returns -1 if one occurs. The function perror() will print a human-readable error message with the given prefix, e.g. open: Permission denied.

// if (fd == -1) {
//     perror("open");
//     exit(1);
// } 
// If weird things are happening like the file's not getting written to, be sure to error-check your syscalls!

// Flushing output
// printf() and other I/O operations in <stdio.h> are buffered. This means they don't necessarily call write() immediately. Syscalls are expensive, so those functions will build up a buffer of output and only send it out from time to time.

// fflush(stdout) causes the buffered output subsystem to call write() immediately.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void) {
    int fd = open("output.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    dup2(fd, 1);

    printf("Hello, world\nThis is a test!\n");
    fflush(stdout);

    close(fd);
}