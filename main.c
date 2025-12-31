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
int status = 0;
char *first_arg = NULL;

(void)argc;

if (env != NULL)
environ = env;

while (1)
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

/* Save first argument before freeing */
first_arg = args[0];

status = execute_command(args, argv[0]);

free(input);
free_args(args);

if (status == 0 && first_arg != NULL && _strcmp(first_arg, "exit") == 0)
{
break;
}
}

return (status);
}
