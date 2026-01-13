#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 2048

void yell_fd(int fd) {
    char buffer[BUFSIZE];
    ssize_t bytes;

    while ((bytes = read(fd, buffer, BUFSIZE)) > 0) {
        for (ssize_t i = 0; i < bytes; i++) {
            buffer[i] = toupper((unsigned char)buffer[i]);
        }
        write(1, buffer, bytes);
    }

    if (bytes == -1) {
        perror("read");
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        yell_fd(0);
    } else {
        for (int i = 1; i < argc; i++) {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                perror(argv[i]);
                continue;
            }
            yell_fd(fd);
            close(fd);
        }
    }
    return 0;
}