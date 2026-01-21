#include <stdio.h>
#include <string.h>

int main(void)
{
    char c[1024];

    fgets(c, sizeof c, stdin);

    char *token;
    int i = 0;

    if ((token = strtok(c, " \n")) != NULL) do {
        printf("%d: %s\n", i++, token);
    } while ((token = strtok(NULL, " \n")) != NULL);
}