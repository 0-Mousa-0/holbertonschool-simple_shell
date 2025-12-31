#include "shell.h"

/**
 * execute_command - Execute a command
 * @args: Array of arguments
 * @prog_name: Program name (argv[0])
 * Return: Exit status of command
 */
int execute_command(char **args, char *prog_name)
{
pid_t pid;
int status;
struct stat st;

if (args[0] == NULL)
return (0);

if (strchr(args[0], '/') != NULL)
{
if (stat(args[0], &st) == 0 && (st.st_mode & S_IXUSR))
{
pid = fork();
if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
_exit(127);
}
}
else if (pid < 0)
{
perror(prog_name);
return (1);
}
else
{
waitpid(pid, &status, 0);
if (WIFEXITED(status))
return (WEXITSTATUS(status));
return (1);
}
}
else
{
fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
return (127);
}
}

fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
return (127);
}
