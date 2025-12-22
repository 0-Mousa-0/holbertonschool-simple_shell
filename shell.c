#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

/**
 * trim_spaces - remove leading and trailing spaces
 * @str: input string
 * Return: pointer to trimmed string (modifies in place)
 */
char *trim_spaces(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';

    return str;
}

/**
 * main - simple UNIX shell
 * Return: 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    char *argv[2];

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#cisfun$ ", 9);

        nread = getline(&line, &len, stdin);

        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        line = trim_spaces(line);

        if (*line == '\0')
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            argv[0] = line;
            argv[1] = NULL;

            if (execve(argv[0], argv, environ) == -1)
            {
                perror("./shell");
                exit(1);
            }
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return 0;
}
