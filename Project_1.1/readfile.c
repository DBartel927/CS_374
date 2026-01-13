#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFSIZE 2048

int main(int argc, char *argv[]) {
    if (argc < 2) {
        write(2, "Usage: readfile <filename>\n", 28);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[BUFSIZE];
    ssize_t bytes_read = read(fd, buffer, BUFSIZE);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    write(1, buffer, bytes_read);

    close(fd);
    return 0;
}