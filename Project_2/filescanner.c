#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define USAGE "usage: filescanner [directory]\n"
#define MAX_PATH_LEN 4096

long scan_directory(const char *path);
int is_dot_dir(const char *name);

int main(int argc, char *argv[]) {
    const char *path = ".";

    if (argc > 2) {
        fprintf(stderr, USAGE);
        return 1;
    }

    if (argc == 2) {
        path = argv[1];
    }

    scan_directory(path);
    return 0;
}

long scan_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat sb;
    char fullpath[MAX_PATH_LEN];
    long total_size = 0;

    dir = opendir(path);
    if (!dir) {
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (is_dot_dir(entry->d_name)) {
            continue;
        }

        if (snprintf(fullpath, sizeof(fullpath), "%s/%s",
                     path, entry->d_name) >= (int)sizeof(fullpath)) {
            continue;
        }

        if (lstat(fullpath, &sb) == -1) {
            continue;
        }

        if (S_ISREG(sb.st_mode)) {
            total_size += sb.st_size;
        } else if (S_ISDIR(sb.st_mode)) {
            total_size += scan_directory(fullpath);
        }
    }

    closedir(dir);

    printf("%s: %ld\n", path, total_size);
    return total_size;
}

int is_dot_dir(const char *name) {
    return (strcmp(name, ".") == 0 || strcmp(name, "..") == 0);
}