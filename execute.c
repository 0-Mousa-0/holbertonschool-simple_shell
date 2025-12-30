#include "shell.h"

/**
 * handle_builtin - Handle built-in commands
 * @args: Array of arguments
 * Return: 1 to continue, 0 to exit
 */
int handle_builtin(char **args)
{
if (_strcmp(args[0], "exit") == 0)
return (exit_shell(args));
else if (_strcmp(args[0], "env") == 0)
return (print_env(args));
else if (_strcmp(args[0], "cd") == 0)
return (change_dir(args));

return (1);
}

/**
 * exit_shell - Exit shell
 * @args: Arguments
 * Return: Never returns (exits the shell)
 */
int exit_shell(char **args)
{
(void)args;
exit(0);  /* Actually exit the program */
}

/**
 * print_env - Print environment variables
 * @args: Arguments
 * Return: 1
 */
int print_env(char **args)
{
char **env = environ;

(void)args;

while (*env)
{
printf("%s\n", *env);
env++;
}

return (1);
}

/**
 * execute_command - Execute a command
 * @args: Array of arguments
 * @prog_name: Program name (argv[0])
 * Return: 1 to continue, 127 for command not found
 */
int execute_command(char **args, char *prog_name)
{
pid_t pid;
int status;
char *full_path;

if (args[0] == NULL)
return (1);

if (is_builtin(args[0]))
return (handle_builtin(args));

full_path = find_executable(args[0]);
if (full_path == NULL)
{
print_error(prog_name, args[0]);
return (127);
}

pid = fork();
if (pid == 0)
{
if (execve(full_path, args, environ) == -1)
{
print_error(prog_name, args[0]);
free(full_path);
_exit(127);
}
}
else if (pid < 0)
{
perror(prog_name);
free(full_path);
}
else
{
waitpid(pid, &status, 0);
free(full_path);
}

return (1);
}
