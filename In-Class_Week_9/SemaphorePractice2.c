// Expected Output
// GOOD—the threads waited correctly:

// Thread 0: sleeping for 2 seconds...
// Thread 1: sleeping for 5 seconds...
// Thread 0: waiting for other thread...
// Thread 1: waiting for other thread...
// Thread 1: complete
// Thread 0: complete
// BAD—Thread 0 did not wait for Thread 1 to finish:

// Thread 0: sleeping for 2 seconds...
// Thread 1: sleeping for 5 seconds...
// Thread 0: waiting for other thread...
// Thread 0: complete
// Thread 1: waiting for other thread...
// Thread 1: complete

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

// TODO: Add some semaphores
sem_t *sem0;
sem_t *sem1;


sem_t *sem_open_temp(const char *name, unsigned int value)
{
    sem_t *sem;

    // Create the semaphore
    if ((sem = sem_open(name, O_CREAT, 0666, value)) == SEM_FAILED)
        return SEM_FAILED;

    // Unlink it so it will go away after this process exits
    if (sem_unlink(name) == -1) {
        sem_close(sem);
        return SEM_FAILED;
    }

    return sem;
}

void *run(void *args)
{
    int *params = args;
    int thread_id = params[0];
    int sleep_time = params[1];

    printf("Thread %d: sleeping for %d seconds...\n", thread_id, sleep_time);
    sleep(sleep_time);

    printf("Thread %d: waiting for other thread...\n", thread_id);

    // TODO: Add rendezvous code!  
    switch (thread_id) {
        case 0:
            sem_post(sem0);
            sem_wait(sem1);
            break;
        case 1:
            sem_post(sem1);
            sem_wait(sem0);
            break;
    }

    printf("Thread %d: complete\n", thread_id);

    return NULL;
}

int main(void)
{
    int params[2][2] = {{0, 2}, {1, 5}};

    pthread_t t0, t1;

    // TODO: Add sem_open_temp() calls
    sem0 = sem_open_temp("/sem0", 0);
    sem1 = sem_open_temp("/sem1", 0);

    pthread_create(&t0, NULL, run, params[0]);
    pthread_create(&t1, NULL, run, params[1]);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    // TODO: Add sem_close() calls
}