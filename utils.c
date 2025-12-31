#include "shell.h"

/**
 * display_prompt - Display shell prompt
 */
void display_prompt(void)
{
printf("$ ");
fflush(stdout);
}

/**
 * read_input - Read input from stdin
 * Return: Input string or NULL on EOF
 */
char *read_input(void)
{
char *line = NULL;
size_t bufsize = 0;
ssize_t nread;

nread = getline(&line, &bufsize, stdin);
if (nread == -1)
{
free(line);
return (NULL);
}

if (nread > 0 && line[nread - 1] == '\n')
line[nread - 1] = '\0';

return (line);
}

/**
 * free_args - Free arguments array
 * @args: Array to free
 */
void free_args(char **args)
{
int i;

if (!args)
return;

for (i = 0; args[i] != NULL; i++)
free(args[i]);

free(args);
}

/**
 * print_error - Print error message
 * @program: Program name
 * @command: Command that failed
 */
void print_error(char *program, char *command)
{
fprintf(stderr, "%s: 1: %s: not found\n", program, command);
}
