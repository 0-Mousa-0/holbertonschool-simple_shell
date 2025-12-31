#include "shell.h"

/**
 * read_line - Read a line from stdin
 * Return: The line read
 */
char *read_line(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

nread = getline(&line, &len, stdin);
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
 * print_error - Print command not found error
 * @command: The command that wasn't found
 */
void print_error(char *command)
{
char error_msg[256];
int len;

(void)command;  /* Mark parameter as unused */
len = snprintf(error_msg, sizeof(error_msg), "./hsh: No such file or directory\n");
write(STDERR_FILENO, error_msg, len);
}
