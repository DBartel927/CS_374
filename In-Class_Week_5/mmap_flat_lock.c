// We have a file full of zero bytes, and we want to fill it with monotonically-increasing integers by repeatedly calling a function that will append the next number.

// The 0th integer in the file is special. It contains the count so far. The rest of the file contains ordered numbers. They start with value 0 at integer index 1 in the file.

// For example, the first 6 integers in the file before calling the append function will look like this:

// 0
// 0
// 0
// 0
// 0
// 0
// After calling the append function 3 times, it will look like this:

// 3   ← The count, remember?
// 0
// 1
// 2
// 0   ← These haven't been changed from zero
// 0
// Your Gains
// More pointer arithmetic.
// Learn array/pointer equivalence.
// How integers are stored as binary instead of text.
// Reinforce mmap() and POSIX locks.
// Get better at reading existing code.
// Get better at fixing concurrency issues.
// What To Do Part I
// Modify the add_next_record() code so that it:

// Gets the count as the 0th byte of the data region.
// Looks forward count integers into the data region (not including the 0th integer used for the count!).
// Sets the value at that location to count.
// Increments the count.
// If you run it at this point, it should spit out a bunch of output indicating incorrect values.

// Hint: You can truncate the output by piping the command to head:

// For example, if I don't have locks I often get several thousand lines of output. I can truncate this to 10 lines like so:

// $ ./mmap_flat_lock | head
//   count = 34946
//   records[3148] == 3149
//   records[4095] == 4096
//   records[4319] == 4321
//   records[4322] == 4323
//   records[4328] == 4330
//   records[4334] == 4335
//   records[4336] == 4337
//   records[4341] == 4342
//   records[4343] == 4344
// What To Do Part II
// What happened?

// Both the parent and child process are appending at the same time in a shared resource.

// Add locks (that lock the entire file region) so that the processes don't step on each others toes.
// After the fix, the only output you should see is:

// count = 40000

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define REC_SIZE 16 // bytes
#define REC_COUNT (1024*1024)
#define FILE_SIZE (REC_SIZE * REC_COUNT)
#define MAX_COUNT 20000

/**
 * Add the next record to the region.
 */
void add_next_record(int fd, void *data)
{
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    lock.l_type   = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start  = 0;
    lock.l_len    = 0;

    fcntl(fd, F_SETLKW, &lock);

    // TODO: Implement me!
    int *count = data;
    int *records = count + 1;
    int current_count = *count;
    records[current_count] = current_count;
    *count = current_count + 1;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
}

/**
 * Main.
 */
int main(void)
{
    int fd;

    if ((fd = open("data.dat", O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1) {
        perror("open");
        return 1;
    }

    ftruncate(fd, FILE_SIZE);

    void *data = mmap(NULL, FILE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    if (data == NULL) {
        perror("mmap");
        return 2;
    }

    int *count = data;
    int *records = count + 1;
    *count = 0;

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 3;
    }

    // Both parent and child are running here

    for (int i = 0; i < MAX_COUNT; i++) {
        add_next_record(fd, data);
    }

    if (pid != 0) {
        // Parent only
        wait(NULL);

        printf("count = %d\n", *count);

        // *2 because both parent and child added MAX_COUNT
        for (int i = 0; i < MAX_COUNT * 2; i++) {
            if (records[i] != i)
                printf("records[%d] == %d\n", i, records[i]);
        }
    }
}