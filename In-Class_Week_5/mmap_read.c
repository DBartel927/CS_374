#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define DATA_SIZE 1024

int main() {
    int fd = open("data.dat", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    void *data = mmap(NULL, DATA_SIZE, PROT_READ, MAP_SHARED, fd, 0);

    int *int_ptr = (int *)data;
    int int_value = *int_ptr;

    float *float_ptr = (float *)(int_ptr + 1);
    float float_value = *float_ptr;

    char *string_ptr = (char *)(float_ptr + 1);
    char string_value[DATA_SIZE - sizeof(int) - sizeof(float)];
    strcpy(string_value, string_ptr);

    printf("Int: %d\n", int_value);
    printf("Float: %f\n", float_value);
    printf("String: %s\n", string_value);

    close(fd);

    return 0;
}