#include <stdio.h>
#include <pthread.h>

#define ARRAY_SIZE 100000
#define THREAD_COUNT 10
int a[ARRAY_SIZE];

void *run(void *args)
{
    (void)args;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i]++;
    }
    return NULL;
}

int main(void)
{
    pthread_t thread[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&(*(thread + i)), NULL, run, NULL);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(thread[i], NULL);
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (a[i] != THREAD_COUNT) {
            printf("a[%d] = %d, expected %d\n", i, a[i], THREAD_COUNT);
        }
    }
}