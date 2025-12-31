#include "shell.h"

/**
 * execute_command - Execute a command with PATH resolution
 * @args: Array of command and arguments
 * Return: Status code
 */
int execute_command(char **args)
{
pid_t pid;
int status;
char *full_path;

if (!args || !args[0])
return (1);

if (is_builtin(args[0]))
return (handle_builtin(args));

full_path = find_command(args[0]);
if (!full_path)
{
print_error(args[0]);
return (127);
}

pid = fork();
if (pid < 0)
{
perror("fork");
free(full_path);
return (1);
}
else if (pid == 0)
{
if (execve(full_path, args, environ) == -1)
{
print_error(args[0]);
free(full_path);
exit(127);
}
}
else
{
waitpid(pid, &status, 0);
free(full_path);
if (WIFEXITED(status))
return (WEXITSTATUS(status));
}

return (1);
}
