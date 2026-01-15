#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void) {
    DIR *dir = opendir("/");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *e;
    while ((e = readdir(dir)) != NULL) {
        printf("%s\n", e->d_name);
    }

    if (closedir(dir) == -1) {
        perror("closedir");
        return 1;
    }

    return 0;
}