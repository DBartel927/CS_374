#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#include "eventbuf.h"

struct eventbuf *buffer;

sem_t *mutex;
sem_t *items;
sem_t *spaces;

int producers;
int consumers;
int events_each;

sem_t *sem_open_temp(const char *name, int value)
{
    sem_t *sem;

    if ((sem = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
        return SEM_FAILED;

    if (sem_unlink(name) == -1) {
        sem_close(sem);
        return SEM_FAILED;
    }

    return sem;
}

void *producer(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < events_each; i++) {

        int event = id * 100 + i;

        sem_wait(spaces);
        sem_wait(mutex);

        eventbuf_add(buffer, event);
        printf("P%d: adding event %d\n", id, event);

        sem_post(mutex);
        sem_post(items);
    }

    printf("P%d: exiting\n", id);
    return NULL;
}

void *consumer(void *arg)
{
    int id = *(int *)arg;

    while (1) {

        sem_wait(items);
        sem_wait(mutex);

        if (eventbuf_empty(buffer)) {
            sem_post(mutex);
            break;
        }

        int event = eventbuf_get(buffer);
        printf("C%d: got event %d\n", id, event);

        sem_post(mutex);
        sem_post(spaces);
    }

    printf("C%d: exiting\n", id);
    return NULL;
}

int main(int argc, char *argv[])
{
    void silencer(int argc);
    {
        (void)argc;  // quiet unused variable error
    }

    producers = atoi(argv[1]);
    consumers = atoi(argv[2]);
    events_each = atoi(argv[3]);
    int max_buffer = atoi(argv[4]);

    buffer = eventbuf_create();

    mutex = sem_open_temp("/mutex", 1);
    items = sem_open_temp("/items", 0);
    spaces = sem_open_temp("/spaces", max_buffer);

    pthread_t prod_threads[producers];
    pthread_t cons_threads[consumers];

    int prod_id[producers];
    int cons_id[consumers];

    for (int i = 0; i < producers; i++) {
        prod_id[i] = i;
        pthread_create(&prod_threads[i], NULL, producer, &prod_id[i]);
    }

    for (int i = 0; i < consumers; i++) {
        cons_id[i] = i;
        pthread_create(&cons_threads[i], NULL, consumer, &cons_id[i]);
    }

    for (int i = 0; i < producers; i++)
        pthread_join(prod_threads[i], NULL);

    for (int i = 0; i < consumers; i++)
        sem_post(items);

    for (int i = 0; i < consumers; i++)
        pthread_join(cons_threads[i], NULL);

    eventbuf_free(buffer);

    sem_close(mutex);
    sem_close(items);
    sem_close(spaces);

    return 0;
}