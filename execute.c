#include "shell.h"

/**
 * handle_builtin - Handle built-in commands
 * @args: Array of arguments
 * Return: 0 for exit, 1 to continue
 */
int handle_builtin(char **args)
{
if (_strcmp(args[0], "exit") == 0)
return (exit_shell(args));

return (1);
}

/**
 * exit_shell - Exit shell
 * @args: Arguments
 * Return: 0 (signals exit)
 */
int exit_shell(char **args)
{
(void)args;
return (0);
}

/**
 * execute_command - Execute a command
 * @args: Array of arguments
 * @prog_name: Program name (argv[0])
 * Return: Exit status of command, 0 for exit
 */
int execute_command(char **args, char *prog_name)
{
pid_t pid;
int status;
char *full_path;

if (args[0] == NULL)
return (0);

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
return (1);
}
else
{
waitpid(pid, &status, 0);
free(full_path);

if (WIFEXITED(status))
{
return (WEXITSTATUS(status));
}
return (1);
}

return (0);
}
