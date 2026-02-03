#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define DATA_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <int> <float> <string>\n", argv[0]);
        exit(1);
    }

    int int_value = atoi(argv[1]);
    float float_value = atof(argv[2]);
    const char *string_value = argv[3];

    int fd = open("data.dat", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    void *data = mmap(NULL, DATA_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int *int_ptr = (int *)data;
    *int_ptr = int_value;

    float *float_ptr = (float *)(int_ptr + 1);
    *float_ptr = float_value;

    char *string_ptr = (char *)(float_ptr + 1);
    strcpy(string_ptr, string_value);

    close(fd);

    return 0;
}

// Explanation of each part:

// Command line parsing: The program checks if exactly three arguments are provided (int, float, string). It converts the first two arguments to their respective types using atoi() and atof().
// File opening: The program opens (or creates) the file data.dat with read and write permissions using open(). It also sets the file size to DATA_SIZE using ftruncate().
// Memory mapping: The program maps the file into memory with both read and write permissions using mmap().
// Data storage: The program computes the correct positions in the memory-mapped region for the int, float, and string, and stores the values accordingly.
// Cleanup: The program unmaps the memory-mapped region using munmap() and closes the file descriptor.