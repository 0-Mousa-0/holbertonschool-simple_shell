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

/* Check for exit command */
if (_strcmp(args[0], "exit") == 0)
{
free(input);
free_args(args);
break;  /* Exit with current status */
}

/* Execute command and save its status */
status = execute_command(args, argv[0]);

free(input);
free_args(args);
}

return (status);
}
