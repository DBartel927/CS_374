#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s \"string\"\n", argv[0]);
        return 1;
    }

    char *s = argv[1];
    char *token;
    int index = 0;

    token = strtok(s, " ");

    while (token != NULL) {
        printf("%d: %s\n", index, token);
        index++;
        token = strtok(NULL, " ");
    }

    return 0;
}