// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main(void)
// {
//     puts("Hello");

//     pid_t pid = fork();

//     printf("PID is %d\n", pid);

//     if (pid == 0) {
//         printf("I'm the child, my PID is %d\n", getpid());
//     } else {
//         printf("I'm the parent, my PID is %d\n", getpid());
//     }

//     puts("World");
// }

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("And...\n");

    pid_t pid = fork();

    if (pid == 0) {
        printf("I'm the child\n");
    } else {
        printf("I'm the parent\n");
    }

    printf("We're done\n");
}