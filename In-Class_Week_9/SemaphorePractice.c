// The Goal
// Part 1: Make it so that only one thread runs at a time.

// You'll launch a number of threads. Each one will print out something like:

// Thread 00: running
// Thread 00: exiting
// with a 1-second sleep between them.

// The goal is to use semaphores, below, to make it so only one thread can run at a time.

// Part 2: Make it so that only three threads can run at a time.

// You should be able to change a single character in your source to make this happen.

// Functions to use
// Use:

// sem_open() to create a semaphore (see below!)
// sem_close() to destroy it
// sem_wait() to wait until it becomes non-negative, then decrement it
// sem_post() to increment it
// Do not use any of the Pthread mutex or condition variable functions.

// The sem_open() call creates a semaphore with a given name (which is a string that you make up at random). Any process can open the semaphore by that name.

// Importantly, the semaphore persists after your process exits unless it is unlinked.

// So to make a semaphore that only exists for the life of this one process, a trick is to create it then immediately unlink it. Here's a function to do that, which I highly recommend you use.

// sem_t *sem_open_temp(const char *name, unsigned int value)
// {
//     sem_t *sem;

//     // Create the semaphore
//     if ((sem = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
//         return SEM_FAILED;

//     // Unlink it so it will go away after this process exits
//     if (sem_unlink(name) == -1) {
//         sem_close(sem);
//         return SEM_FAILED;
//     }

//     return sem;
// }

#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREAD_COUNT 15

#define MAX_RUNNERS 3

sem_t *sem;

sem_t *sem_open_temp(const char *name, unsigned int value)
{
    sem_t *s;

    // Create the semaphore
    if ((s = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
        return SEM_FAILED;

    // Unlink it so it will go away after this process exits
    if (sem_unlink(name) == -1) {
        sem_close(s);
        return SEM_FAILED;
    }

    return s;
}

void *run(void *arg)
{
    int *id = arg;

    sem_wait(sem);

    printf("Thread %02d: running\n", *id);

    sleep(1);  // This is important work

    printf("Thread %02d: exiting\n", *id);

    sem_post(sem);

    return NULL;
}

int main(void)
{
    // You can add code here, but...

    sem = sem_open_temp("/my_semaphore", MAX_RUNNERS);  // Only three threads can run at a time

    // Do not modify code between these marks vvv
    pthread_t runners[THREAD_COUNT];
    int runner_id[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        runner_id[i] = i;
        pthread_create(runners + i, NULL, run, runner_id + i);  // Run, runner!
    }

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_join(runners[i], NULL);
    // Do not modify code between these marks ^^^
    sem_close(sem);
}