#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define RECORD_SIZE   32
#define RECORD_COUNT  1048576
#define HEADER_SIZE   (sizeof(int) * 2)
#define FILE_SIZE     (HEADER_SIZE + RECORD_SIZE * RECORD_COUNT)
#define MAX_PAIRS     5

void lock_region(int fd, int type, off_t offset, off_t length) {
    struct flock fl;
    fl.l_type   = type;
    fl.l_whence = SEEK_SET;
    fl.l_start  = offset;
    fl.l_len    = length;
    fcntl(fd, F_SETLKW, &fl);
}

void unlock_region(int fd, off_t offset, off_t length) {
    struct flock fl;
    fl.l_type   = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start  = offset;
    fl.l_len    = length;
    fcntl(fd, F_SETLK, &fl);
}

void append_record(int fd, void *data, const char *prefix, int serial) {
    int *offset_ptr = (int *)data;
    int *count_ptr  = offset_ptr + 1;

    int local_offset;

    lock_region(fd, F_WRLCK, 0, HEADER_SIZE);

    local_offset = *offset_ptr;
    (*count_ptr)++;
    *offset_ptr += RECORD_SIZE;

    unlock_region(fd, 0, HEADER_SIZE);

    char *record_base = (char *)data + HEADER_SIZE + local_offset;

    lock_region(fd, F_WRLCK, HEADER_SIZE + local_offset, RECORD_SIZE);

    snprintf(record_base, RECORD_SIZE, "%s %d", prefix, serial);

    unlock_region(fd, HEADER_SIZE + local_offset, RECORD_SIZE);
}

int main(int argc, char *argv[]) {
    if ((argc - 1) % 2 != 0 || argc < 3) {
        fprintf(stderr, "Usage: %s <count> <prefix> [count prefix ...]\n", argv[0]);
        exit(1);
    }

    int fd = open("appendlog.dat", O_RDWR | O_CREAT | O_TRUNC, 0666);

    ftruncate(fd, FILE_SIZE);

    void *data = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int pair_count = (argc - 1) / 2;

    for (int i = 0; i < pair_count; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            int count = atoi(argv[1 + i * 2]);
            const char *prefix = argv[2 + i * 2];

            for (int j = 0; j < count; j++) {
                append_record(fd, data, prefix, j);
            }
            exit(0);
        }
    }

    for (int i = 0; i < pair_count; i++) {
        wait(NULL);
    }

    lock_region(fd, F_RDLCK, 0, FILE_SIZE);

    int *offset_ptr = (int *)data;
    int *count_ptr  = offset_ptr + 1;
    int count = *count_ptr;

    char *records = (char *)data + HEADER_SIZE;

    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, records + i * RECORD_SIZE);
    }

    unlock_region(fd, 0, FILE_SIZE);

    munmap(data, FILE_SIZE);
    close(fd);

    return 0;
}