#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

void usage(void) {
    fprintf(stderr, "usage: mymkdir dir\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        return 1;
    }

    const char *dir_name = argv[1];
    if (mkdir(dir_name, 0755) == -1) {
        perror(dir_name);
        return 1;
    }

    return 0;
}