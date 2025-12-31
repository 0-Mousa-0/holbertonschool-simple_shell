#include "shell.h"

char **tokenize(char *line)
{
    int bufsize = 64, i = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) return (NULL);

    /* strtok automatically skips leading/multiple delimiters */
    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[i] = NULL;
    return (tokens);
}
