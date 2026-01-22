#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char *tokens[128] = {0};

    char c[1024];

    printf("prompt> ");
    fflush(stdout);

    if (fgets(c, sizeof c, stdin) == NULL)
        return 0;

    char *token;
    int i = 0;

    if ((token = strtok(c, " \n")) != NULL) do {
        tokens[i++] = token;
    } while ((token = strtok(NULL, " \n")) != NULL);

    if (tokens[0] == NULL)
        return 0;

    execvp(tokens[0], tokens);

    perror("execvp");
    return 1;
}