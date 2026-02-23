// Fix the race condition by adding mutexes.

// Experiment with where the mutexes are placed.

// Add mutexes.

// Increase the size of the array until the program takes between 0-1 seconds to run.

// You can time the program with the Unix time command:

// $ time ./progname
// If the mutexes are outside the loop, move them inside around the increment, or vice-versa.

// Redo the timing.

// What accounts for the time difference?

#include <stdio.h>
#include <pthread.h>

#define ELEMENTS 100000
#define THREADS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int a[ELEMENTS] = {0};

volatile int spinlock1 = 0;

void lock(void) {
    while (__sync_lock_test_and_set(&spinlock1, 1))
        ;
}

void unlock(void) {
    __sync_synchronize(); // Memory barrier.
    spinlock1 = 0;
}

void *run(void *arg)
{
    (void)arg;

    // pthread_mutex_lock(&mutex);
    // lock();
    for (int i = 0; i < ELEMENTS; i++) {
        // pthread_mutex_lock(&mutex);
        lock();
        a[i]++;
        // pthread_mutex_unlock(&mutex);
        unlock();
    }
    // pthread_mutex_unlock(&mutex);
    // unlock();
    return NULL;
}

int main(void)
{
    pthread_t thread[THREADS];

    for (int i = 0; i < THREADS; i++)
        pthread_create(thread + i, NULL, run, NULL);

    for (int i = 0; i < THREADS; i++)
        pthread_join(thread[i], NULL);

    int expected = THREADS;

    for (int i = 0; i < ELEMENTS; i++)
        if (a[i] != expected)
            printf("a[%d] = %d, expected %d\n", i, a[i], expected);
}

// Speculate on what accounts for the time difference if the mutexes were inside or outside the loop.

// The difference was all in how much overhead it is to set up threads vs. setting up mutexes. If the mutex is outside the loop, less locks are made but paralellism is all but eliminated. If the mutex is inside the loop, paralellism is retained but more mutexes have to be made. In this example system, it turned out that the loss of paralellism still saved more time.

// Speculate on what accounts for the speed difference when using the spinlock in part 3.

// The same thing happens here, where the paralellism gain from making the locks operate iside the loop does not make up for the cost of repeatedly setting up multiple locks.