// Identify the problem.
// Add a mutex to prevent it from occurring.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 4
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int shared_value = 1;

void *run(void *arg)
{
    (void)arg;

    pthread_mutex_lock(&mutex);
        
    if (shared_value > 0) {
        usleep(1);
        shared_value--;
    }

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_create(threads + i, NULL, run, NULL);

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_join(threads[i], NULL);

    if (shared_value < 0)
        printf("How'd shared_value get to be %d?\n", shared_value);
    else
        puts("OK");
}

// The program runs 4 threads. Can the problem also manifest with only 2 threads? What about only 1 thread?

// With 2 threads, the problem can still manifest. If both threads read the value of shared_value as 1 before either thread decrements it, both threads will proceed to decrement it, resulting in shared_value becoming -1. With only 1 thread, the problem cannot manifest because there is no concurrent access to shared_value; the single thread will read, decrement, and write back the value without interference from another thread.

// Explain exactly what steps threads must individually take for shared_value to fall below 0.

// 1. Thread A reads shared_value and sees that it is 1.
// 2. Thread B reads shared_value and sees that it is 1.
// 3. Threads A and B both decrement shared_value by 1.
// 4. The value of shared_value is now -1.