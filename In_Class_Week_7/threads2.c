#include <stdio.h>
#include <pthread.h>

struct thread_args {
    const char *hello_msg;
    const char *goodbye_msg;
};

void *run(void *args)
{
    (void)args;
    struct thread_args *thread_args = (struct thread_args *)args;
    puts(thread_args->hello_msg);
    puts(thread_args->goodbye_msg);

    return NULL;
}

int main(void)
{
    pthread_t t1;

    puts("parent: hello!");

    struct thread_args args = {
        .hello_msg = "child: hello!",
        .goodbye_msg = "child: goodbye!"
    };

    pthread_create(&t1, NULL, run, &args);

    pthread_join(t1, NULL);

    puts("parent: goodbye!");
}