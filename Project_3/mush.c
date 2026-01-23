#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 2048
#define MAX_TOKENS 128
#define PROMPT "mush> "

void run_command(char *tokens[])
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        execvp(tokens[0], tokens);

        perror("execvp");
        exit(1);
    } else {
        wait(NULL);
    }
}

int main(void)
{
    char line[MAX_LINE];
    char *tokens[MAX_TOKENS];

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        if (fgets(line, sizeof line, stdin) == NULL) {
            putchar('\n');
            break;
        }

        memset(tokens, 0, sizeof tokens);

        char *token;
        int i = 0;

        token = strtok(line, " \n");
        while (token != NULL && i < MAX_TOKENS - 1) {
            tokens[i++] = token;
            token = strtok(NULL, " \n");
        }
        tokens[i] = NULL;

        if (tokens[0] == NULL)
            continue;

        if (strcmp(tokens[0], "exit") == 0) {
            exit(0);
        }

        if (strcmp(tokens[0], "cd") == 0) {
            if (tokens[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(tokens[1]) == -1) {
                perror("cd");
            }
            continue;
        }

        run_command(tokens);
    }

    return 0;
}