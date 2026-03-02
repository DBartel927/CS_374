// We'll have a shared, global count variable. We'll have a mutex protecting it.

// The rules are:

// If you read count, it must be under the mutex.
// If you write count, it must be under the mutex.
// If you wait for a condition variable, it must be under the mutex.
// If you signal the condition variable, it must be under the mutex.
// You must release the mutex as soon as possible so that other threads can run.
// Mutex Refresher
// A global mutex:

// pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
// Acquiring and releasing:

// pthread_mutex_lock(&my_mutex);
// pthread_mutex_unlock(&my_mutex);
// Condition Variable Refresher
// A global condition variable:

// pthread_cond_t my_cond = PTHREAD_COND_INITIALIZER;
// Waiting for a notification:

// pthread_cond_wait(&my_cond, &count_mutex);
// Signaling (notifying):

// pthread_cond_signal(&my_cond);    // to one waiting thread
// pthread_cond_broadcast(&my_cond); // to all waiting threads
// Importantly when you pthread_cond_wait(), it will unlock the mutex until signaled, at which point it will reacquire it before the program continues. It does all this behind your back. This allows other threads to run while you're waiting under the mutex.

// What Condition Variables Are Not
// We have a variable count we'll use in this challenge, but this isn't strictly attached to the condition variable. So don't get them confused. We're only using the condition variable to signal to another thread that count has changed.

// Threads Refresher
// Here's some skeleton thread code, in case you've forgotten the pattern:

// #include <pthread.h>

// void *run(void *arg)
// {
//     (void)arg;

//     // Do things

//     return NULL;
// }

// int main(void)
// {
//     pthread_t t1;

//     pthread_create(&t1, NULL, run1, NULL);

//     // Maybe do things

//     pthread_join(t1, NULL);
// }
// What To Do
// We want a global count variable and two threads. (The main thread can be the second thread, or you can launch two if you prefer.)

// One thread will do effectively this (pseudocode):

// while (count < 5):
//     count++
//     print "Thread 1: count is {count}"
//     pthread_cond_signal
//     sleep(1 second)
// The other thread will do effectively this:

// while (count < 5):
//     pthread_cond_wait
//     print "Thread 1: count is {count}"
// See how it works? One thread is responsible for incrementing the count and signaling the other that the count has been incremented.

// And the other thread just waits for the signal and then prints out what it sees.

// BUT you have to figure out how to lock and unlock all this. Remember the rules:

// If you read count, it must be under the mutex.
// If you write count, it must be under the mutex.
// If you wait for a condition variable, it must be under the mutex.
// If you signal the condition variable, it must be under the mutex.
// You must release the mutex as soon as possible so that other threads can run.
// You're going to end up with at least one gnarly-looking loop.

// Hints: Don't fear infinite loops with a break inside. And be sure to unlock the mutex on all conditional paths.

// Example Output
// Thread 1, count is 1
// Thread 2, count is 1
// Thread 1, count is 2
// Thread 2, count is 2
// Thread 1, count is 3
// Thread 2, count is 3
// Thread 1, count is 4
// Thread 2, count is 4
// Thread 1, count is 5
// Thread 2, count is 5
// But there's a chance you might see this where Thread 2 never prints a count of 1:

// Thread 1, count is 1
// Thread 1, count is 2  <-- Where's Thread 2?
// Thread 2, count is 2
// Thread 1, count is 3
// Thread 2, count is 3
// Thread 1, count is 4
// Thread 2, count is 4
// Thread 1, count is 5
// Thread 2, count is 5
// If you do see this, why is it happening? How might you change it so that Thread 2 does see the count of 1?

// Try this: before Thread 2 does anything, have it sleep(3). What happens to the earlier pthread_cond_signal() calls from Thread 1?

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

        if (count >= 5) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        count++;
        printf("Thread 1, count is %d\n", count);

        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1;

    pthread_create(&t1, NULL, run, NULL);

    while (1) {
        pthread_mutex_lock(&mutex);

        if (count >= 5) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_cond_wait(&cond, &mutex);
        printf("Thread 2, count is %d\n", count);

        pthread_mutex_unlock(&mutex);
    }

    pthread_join(t1, NULL);
}