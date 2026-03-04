// The Overview
// The idea is that we're going to have all the threads pile up at the barrier and then, one at a time, go through the turnstile. They'll all be waiting there for the turnstile to open.

// The turnstile is closed to start. Let's say you have 10 threads (the total number of threads is given).

// Once the 10th thread arrives outside the turnstile, it opens the turnstile and one thread gets past (maybe the 10th thread, or maybe another one—depends on the scheduler).

// The thread that gets past the turnstile optionally does some work and then, just before leaving, it opens the turnstile again. This allows another thread to get through it.

// And then the process repeats until all 10 threads are through.

// Imagine you launch a large number of threads to be ready to, say, handle network requests, but they shouldn't start doing so until the system has fully started up. You could use a barrier to have them wait.

// And the work they do past the turnstile is optional. You can have them do the work before letting another thread past (thus throttling how many threads are doing work at once), or you could just instantly let the next past, which is just a plain barrier. We're going to do something like this:

// Algorithm
// All threads use this flow, assuming the count is 0 to start:

// Increment count
// If count == total_thread_count:
// Open the turnstile
// Wait for the turnstile to open
// Pass the turnstile, automatically closing it
// Optionally do work
// Open the turnstile
// Go about your business
// Now, count is going to be a global that's shared between threads. If you have a shared resource that you're writing to, you have to do what with it? Lock it. For this challenge, we won't use a Pthread mutex—we'll use a semaphore acting as a mutex.

// If you want to slow the run you can have the thread sleep(1); at the "Optionally do work" phase, above. Not necessary for this demo, though.

// Semaphore Mutex Refresher
// To make a mutex from a semaphore:

// Initialize the semaphore with a value of 1 (meaning anyone who waits will immediately get it).
// To lock the mutex:

// Wait on the semaphore. (This will wait until it becomes 1 and then decrement it to 0.)
// To unlock the mutex:

// Post to the semaphore. (This will increment it back to 1.)
// Remember to only hold the mutex for as long as you need to. Also remember that only one thread (the last one) should do the initial opening of the turnstile.

// Semaphores Needed
// You'll need two:

// One for the mutex over count.
// One to act as the turnstile.
// Consider: what should the turnstile semaphore be initialized to?
// Starter Code
// #include <stdio.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <pthread.h>
// #include <semaphore.h>

// #define THREAD_COUNT 10

// // TODO: Add some semaphores
// // TODO: Add a global `count` variable

// sem_t *sem_open_temp(const char *name, unsigned int value)
// {
//     sem_t *sem;

//     // Create the semaphore
//     if ((sem = sem_open(name, O_CREAT, 0666, value)) == SEM_FAILED)
//         return SEM_FAILED;

//     // Unlink it so it will go away after this process exits
//     if (sem_unlink(name) == -1) {
//         sem_close(sem);
//         return SEM_FAILED;
//     }

//     return sem;
// }

// void *run(void *args)
// {
//     int thread_id = *(int*)args;

//     (void)thread_id;  // quiet unused variable warning

//     // TODO: Add turnstile stuff

//     return NULL;
// }

// int main(void)
// {
//     pthread_t thread[THREAD_COUNT];
//     int thread_id[THREAD_COUNT];

//     // TODO: Add sem_open_temp() calls

//     for (int i = 0; i < THREAD_COUNT; i++) {
//         thread_id[i] = i;
//         pthread_create(thread + i, NULL, run, thread_id + i);
//     }

//     for (int i = 0; i < THREAD_COUNT; i++)
//         pthread_join(thread[i], NULL);

//     // TODO: Add sem_close() calls
// }
// Example Output
// For this output, I printed:

// "Waiting" each time I waited on the turnstile.
// "Opening" for the first thread to post to the turnstile (the one who found the count had reached 10).
// "In turnstile" after a thread got past the turnstile wait.
// "Reopening" when it posted to the turnstile after doing the work.
// "Complete" when the thread is about to exit.
// Notice how all the threads arrived at the barrier before the turnstile opened.

// Also, I decremented the count after a thread got through, and I added some output in the main thread after everything had been joined just to verify that the count was back to 0.

// Thread 0: Waiting for turnstile
// Thread 2: Waiting for turnstile
// Thread 1: Waiting for turnstile
// Thread 3: Waiting for turnstile
// Thread 4: Waiting for turnstile
// Thread 5: Waiting for turnstile
// Thread 6: Waiting for turnstile
// Thread 7: Waiting for turnstile
// Thread 8: Waiting for turnstile
// Thread 9: Opening turnstile
// Thread 9: Waiting for turnstile
// Thread 9: In turnstile
// Thread 9: Reopening turnstile
// Thread 9: complete
// Thread 0: In turnstile
// Thread 0: Reopening turnstile
// Thread 0: complete
// Thread 1: In turnstile
// Thread 1: Reopening turnstile
// Thread 1: complete
// Thread 3: In turnstile
// Thread 3: Reopening turnstile
// Thread 3: complete
// Thread 4: In turnstile
// Thread 4: Reopening turnstile
// Thread 4: complete
// Thread 5: In turnstile
// Thread 5: Reopening turnstile
// Thread 5: complete
// Thread 6: In turnstile
// Thread 6: Reopening turnstile
// Thread 6: complete
// Thread 7: In turnstile
// Thread 7: Reopening turnstile
// Thread 7: complete
// Thread 8: In turnstile
// Thread 8: Reopening turnstile
// Thread 8: complete
// Thread 2: In turnstile
// Thread 2: Reopening turnstile
// Thread 2: complete
// Count should be 0, and it is 0.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_COUNT 10
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// TODO: Add some semaphores
// TODO: Add a global `count` variable

sem_t *mutex;
sem_t *turnstile;
int count = 0;

sem_t *sem_open_temp(const char *name, unsigned int value)
{
    sem_t *s;

    // Create the semaphore
    if ((s = sem_open(name, O_CREAT, 0666, value)) == SEM_FAILED)
        return SEM_FAILED;

    // Unlink it so it will go away after this process exits
    if (sem_unlink(name) == -1) {
        sem_close(s);
        return SEM_FAILED;
    }

    return s;
}

void *run(void *args)
{
    int thread_id = *(int*)args;

    (void)thread_id;  // quiet unused variable warning

    // TODO: Add turnstile stuff

    sem_wait(mutex);
    count++;
    if (count == THREAD_COUNT) {
        printf("Thread %d: Opening turnstile\n", thread_id);
        sem_post(turnstile);
    }
    // pthread_mutex_unlock(&mutex);
    sem_post(mutex);

    printf("Thread %d: Waiting for turnstile\n", thread_id);
    sem_wait(turnstile);

    printf("Thread %d: In turnstile\n", thread_id);

    printf("Thread %d: Reopening turnstile\n", thread_id);
    sem_post(turnstile);

    sem_wait(mutex);
    count--;
    sem_post(mutex);

    printf("Thread %d: complete\n", thread_id);

    return NULL;
}

int main(void)
{
    pthread_t thread[THREAD_COUNT];
    int thread_id[THREAD_COUNT];

    // TODO: Add sem_open_temp() calls
    mutex = sem_open_temp("/mutex", 1);
    turnstile = sem_open_temp("/turn", 0);

    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_id[i] = i;
        pthread_create(thread + i, NULL, run, thread_id + i);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_join(thread[i], NULL);

    // TODO: Add sem_close() calls
    printf("Count should be 0, and it is %d.\n", count);
    sem_close(mutex);
    sem_close(turnstile);
}