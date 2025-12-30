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
int status = 0;  /* Default exit status */

(void)argc;

if (env != NULL)
environ = env;

while (1)
{
if (isatty(STDIN_FILENO))
display_prompt();

input = read_input();
if (input == NULL)
break;  /* EOF exits with current status */

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

if (status == 0 && args[0] != NULL && _strcmp(args[0], "exit") == 0)
{
/* Exit built-in was called */
break;
}
}

return (status);  /* Return last command status */
}
