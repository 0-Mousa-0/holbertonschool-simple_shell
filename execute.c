#include "shell.h"

int execute_command(char **args, char *prog_name)
{
pid_t pid;
int status;
char *full_path;

if (args[0] == NULL)
return (0);

if (_strcmp(args[0], "exit") == 0)
return (0);

/* Check if command contains '/' */
if (has_slash(args[0]))
{
/* Absolute or relative path - check if exists */
if (access(args[0], F_OK) == 0)
{
/* Command exists - fork and execute */
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
/* Command with '/' doesn't exist - NO FORK */
fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
return (127);
}
}

/* Command without '/' - search in PATH */
full_path = find_in_path(args[0]);
if (full_path == NULL)
{
/* Command not found in PATH - NO FORK */
fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
return (127);
}

/* Command found - fork and execute */
pid = fork();
if (pid == 0)
{
if (execve(full_path, args, environ) == -1)
{
free(full_path);
fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
_exit(127);
}
}
else if (pid < 0)
{
free(full_path);
perror(prog_name);
return (1);
}
else
{
waitpid(pid, &status, 0);
free(full_path);
if (WIFEXITED(status))
return (WEXITSTATUS(status));
return (1);
}

return (0);
}
