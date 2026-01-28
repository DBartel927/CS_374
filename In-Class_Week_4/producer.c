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

// This is the producer program.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        exit(1);
    }

    const char *fifo_name = "my_fifo";

    if (mkfifo(fifo_name, 0666) == -1) {
    }

    int fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}

// When the producers are run, they run with the parameters given (in this case "foo" and "bar") and stop. On the command line, this results in creating a newline and waiting. When the consumer is run, it loops through everything in the fifo and reads it all. The acronym FIFO also being used to represent first in first out, and the pipe seems to work the same way, printing "foobar". It prints out the contents into stout, so it is displayed on the command line.