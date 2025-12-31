#include "shell.h"

void display_prompt(void)
{
printf("$ ");
fflush(stdout);
}

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

void free_args(char **args)
{
int i;

if (!args)
return;

for (i = 0; args[i] != NULL; i++)
free(args[i]);

free(args);
}
