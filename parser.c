#include "shell.h"

/**
 * parse_input - Parse input line into arguments
 * @input: Input string
 * Return: Array of arguments or NULL
 */
char **parse_input(char *input)
{
int bufsize = 64;
int position = 0;
char **args = malloc(bufsize * sizeof(char *));
char *token;

if (!args)
return (NULL);

token = strtok(input, " \t\r\n");
while (token != NULL)
{
if (token[0] != '\0')
{
args[position] = _strdup(token);
if (!args[position])
{
free_args(args);
return (NULL);
}
position++;

if (position >= bufsize)
{
bufsize += 64;
args = realloc(args, bufsize * sizeof(char *));
if (!args)
return (NULL);
}
}
token = strtok(NULL, " \t\r\n");
}

args[position] = NULL;
return (args);
}

/**
 * is_builtin - Check if command is built-in
 * @command: Command to check
 * Return: 1 if built-in, 0 otherwise
 */
int is_builtin(char *command)
{
char *builtins[] = {"exit", "env", "cd", NULL};
int i;

if (!command)
return (0);

for (i = 0; builtins[i]; i++)
{
if (_strcmp(command, builtins[i]) == 0)
return (1);
}
return (0);
}
