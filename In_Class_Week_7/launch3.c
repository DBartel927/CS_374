#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 2

pthread_t thread[THREAD_COUNT];

void *run(void *args)
{
    (void)args;
    puts("running");
    return NULL;
}

int main(void)
{
    puts("main thread beginning");

    for (int i = 0; i < THREAD_COUNT; i++) {
        // pthread_create(&thread[i], NULL, run, NULL);
        pthread_create(&(*(thread + i)), NULL, run, NULL);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(thread[i], NULL);
    }

    puts("main thread complete");
}