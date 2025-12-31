#include "shell.h"

/**
 * parse_line - Parse a line into arguments
 * @line: The line to parse
 * Return: Array of arguments
 */
char **parse_line(char *line)
{
char **args = malloc(64 * sizeof(char *));
char *token;
int i = 0;

if (!args)
{
perror("malloc");
return (NULL);
}

token = strtok(line, " \t\n");
while (token)
{
args[i] = strdup(token);
if (!args[i])
{
perror("strdup");
free_args(args);
return (NULL);
}
i++;
token = strtok(NULL, " \t\n");
}
args[i] = NULL;

return (args);
}

/**
 * free_args - Free an array of arguments
 * @args: Array to free
 */
void free_args(char **args)
{
int i;

if (!args)
return;

for (i = 0; args[i]; i++)
free(args[i]);

free(args);
}
