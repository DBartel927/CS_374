// This challenge will involve three threads.

// Main thread: Launch thread#1
// Main thread: Launch thread#2
// Main thread: Set the value of a global to 6
// Thread#1   : Wait until the value of the global to get to 3
//            : When it does, print "Half way there!" and exit

// Thread#2   : Wait until the value of the global to get to 0
//            : When it does, print "Liftoff!" and exit
// Main thread: Loop, decrementing the value while it's greater than 0
//            : Broadcast to all the waiting threads.
//            : Sleep 1 second between decrements!
// Main thread: Join the two child threads
// Use mutexes and condition variables to solve this challenge.

// The main thread can use sleep(1); from <unistd.h> to sleep for a second.

// Example output (noting that 6 is skipped since I was decrementing before the print):

// 5
// 4
// 3
// Half way there!
// 2
// 1
// 0
// Liftoff!

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int count = 0;

void *run(void *arg)
{
    (void)arg;

    while (1) {
        pthread_mutex_lock(&mutex);

        if (count == 3) {
            printf("Half way there!\n");
            sleep(1);
            pthread_mutex_unlock(&mutex);
            break;
        }

        if (count == 0) {
            printf("Liftoff!\n");
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_cond_wait(&cond, &mutex);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    count = 6;

    pthread_create(&t1, NULL, run, NULL);
    pthread_create(&t2, NULL, run, NULL);

    while (count > 0) {
        printf("%d\n", count);
        count--;

        pthread_cond_broadcast(&cond);

        sleep(1);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}