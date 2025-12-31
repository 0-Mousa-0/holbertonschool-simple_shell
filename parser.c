#include "shell.h"

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
