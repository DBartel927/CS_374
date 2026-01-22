#include <stdio.h>
#include <string.h>

int main(void)
{
    char *tokens[128] = {0};

    char c[1024];
    fgets(c, sizeof c, stdin);

    char *token;
    int i = 0;

    if ((token = strtok(c, " \n")) != NULL) do {
        tokens[i++] = token;
    } while ((token = strtok(NULL, " \n")) != NULL);

    for (int i = 0; tokens[i] != NULL; i++)
        printf("%d: %s\n", i, tokens[i]);
}