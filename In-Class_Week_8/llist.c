// Copy the skeleton code, below, into llist.c. Compile it to llist.

// Run it as the example run, above. Should be fine even through multiple runs.

// Change THREAD_COUNT to 2.

// Repeat the runs for ./llist 0, ./llist 1, and ./llist 2 multiple times. Observe what happens.

// Add locks for case 0 and get that running consistently.

// Same for cases 1 and 2.

// Run them multiple times with THREAD_COUNT set to 8 just to be sure. (The resultant linked lists with be exactly 8x longer than just a single thread.)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 8
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Linked list node.
 */
struct node {
    int value;
    struct node *next;
};

/**
 * Insert at head of a linked list.
 */
void llist_insert(struct node **head, int value)
{
    struct node *n = malloc(sizeof *n);
    n->value = value;
    usleep(1); // IGNORE all usleeps! Leave them in place.
    n->next = *head;
    usleep(1);
    *head = n;
}

/**
 * Delete head of a linked list.
 */
void llist_delete(struct node **head)
{
    if (*head == NULL) {
        return;
    }

    struct node *n = *head;
    usleep(1);
    struct node *next = (*head)->next;
    usleep(1);
    *head = next;

    free(n);
}

/**
 * Append to end of linked list.
 */
void llist_append(struct node **head, int value)
{
    struct node *n = malloc(sizeof *n);
    n->value = value;
    n->next = NULL;
    if (*head == NULL) {
        *head = n;
        return;
    }

    pthread_mutex_lock(&mutex);
    struct node *p = *head;

    while (p->next != NULL) {
        usleep(1);
        p = p->next;
    }

    usleep(1);
    p->next = n;
    pthread_mutex_unlock(&mutex);
}

/**
 * Traverse a linked list, calling function f() on each node in turn.
 */
void llist_traverse(struct node *head, void(*f)(struct node *))
{
    for (struct node *p = head; p != NULL; p = p->next)
        f(p);
}

/**
 * Print a single linked list node.
 */
void print_node(struct node *n)
{
    printf("[%d]%s", n->value, n->next? "->": "->NULL");
}

/**
 * Print an entire list.
 */
void llist_print(struct node *head)
{
    if (head == NULL) {
        puts("[EMPTY]");
        return;
    }

    llist_traverse(head, print_node);
    putchar('\n');
}

/**
 * Thread run function to test appends.
 */
void *run_append(void *arg)
{
    struct node **head = arg;

    for (int i = 0; i < 10; i++) {
        llist_append(head, i);
    }

    return NULL;
}

/**
 * Thread run function to test inserts.
 */
void *run_insert(void *arg)
{
    struct node **head = arg;

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10; i++) {
        llist_insert(head, i);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

/**
 * Thread run function to test inserts and deletes.
 */
void *run_insert_delete(void *arg)
{
    pthread_mutex_lock(&mutex);
    struct node **head = arg;

    for (int i = 0; i < 10; i++) {
        llist_insert(head, i);
    }

    for (int i = 0; i < 10; i++) {
        llist_delete(head);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

/**
 * Main.
 */
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s 0|1|2\n", argv[0]);
        return 1;
    }

    pthread_t threads[THREAD_COUNT];

    struct node *head = NULL;

    for (int i = 0; i < THREAD_COUNT; i++) {
        switch (argv[1][0]) {
        case '0':
            pthread_create(threads + i, NULL, run_append, &head);
            break;
        case '1':
            pthread_create(threads + i, NULL, run_insert, &head);
            break;
        case '2':
            pthread_create(threads + i, NULL, run_insert_delete, &head);
            break;
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    llist_print(head);
}