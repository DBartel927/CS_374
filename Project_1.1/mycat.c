#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFSIZE 2048

void copy_fd(int fd) {
    char buffer[BUFSIZE];
    ssize_t bytes;

    while ((bytes = read(fd, buffer, BUFSIZE)) > 0) {
        write(1, buffer, bytes);
    }

    if (bytes == -1) {
        perror("read");
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        copy_fd(0);  // stdin
    } else {
        for (int i = 1; i < argc; i++) {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                perror(argv[i]);
                continue;
            }
            copy_fd(fd);
            close(fd);
        }
    }
    return 0;
}