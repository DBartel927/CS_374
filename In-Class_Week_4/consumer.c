// In this challenge, we'll make a FIFO and use it.

// What to Do
// Write a producer program that opens the FIFO for writing and writes whatever the user specified in argv[1]. Then closes and exits.

// Write a consumer program that opens the FIFO for reading and, in a loop, repeatedly reads data from the FIFO and prints it to stdout.

// Both these programs should first try to make a new FIFO (of the same name—your choice) with mkfifo(). If it already exists, mkfifo() will fail and that's fine.

// Open three windows and run the following in order:

// Window 1: ./producer foo
// Window 2: ./producer bar
// Window 3: ./consumer
// What happens when you run the producers?

// Then what happens when you run the consumer?

// This is the consumer program.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    const char *fifo_name = "my_fifo";

    if (mkfifo(fifo_name, 0666) == -1) {
    }

    int fd = open(fifo_name, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char buffer[4028];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s\n", buffer);
        fflush(stdout);
    }

    close(fd);

    return 0;
}