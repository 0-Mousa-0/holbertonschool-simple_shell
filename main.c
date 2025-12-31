#include "shell.h"

/**
 * main - Simple shell main function
 * Return: Always 0
 */
int main(void)
{
char *line;
char **args;
int status = 0;
int interactive = isatty(STDIN_FILENO);

while (1)
{
if (interactive)
write(STDOUT_FILENO, "$ ", 2);

line = read_line();
if (!line)
{
if (interactive)
write(STDOUT_FILENO, "\n", 1);
break;
}

args = parse_line(line);
if (!args)
{
free(line);
continue;
}

if (args[0])
status = execute_command(args);

free(line);
free_args(args);
}

return (status);
}
