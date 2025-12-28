#include "shell.h"

/**
 * main - Simple shell entry point
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 * Return: Exit status
 */
int main(int argc, char **argv, char **env)
{
char *input = NULL;
char **args = NULL;
int status = 1;

(void)argc;

if (env != NULL)
environ = env;

while (status)
{
if (isatty(STDIN_FILENO))
display_prompt();

input = read_input();
if (input == NULL)
break;

args = parse_input(input);
if (args == NULL || args[0] == NULL)
{
free(input);
free_args(args);
continue;
}

status = execute_command(args, argv[0]);

free(input);
free_args(args);
}

return (0);
}
