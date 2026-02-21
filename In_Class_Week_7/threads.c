#include <stdio.h>
#include <pthread.h>

void *run(void *args)
{
    (void)args;
    puts("child: hello!");
    puts("child: goodbye!");

    return NULL;
}

int main(void)
{
    pthread_t t1;

    puts("parent: hello!");

    pthread_create(&t1, NULL, run, NULL);

    pthread_join(t1, NULL);

    puts("parent: goodbye!");
}