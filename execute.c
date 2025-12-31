#include "shell.h"

/**
 * execute - Forks a process and executes the command
 * @args: Command and arguments
 * @path: The resolved path to the executable
 * Return: The exit status of the child process
 */
int execute(char **args, char *path)
{
	pid_t pid;
	int status;
	int exit_s = 0;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror("Error");
			exit(126); /* Command found but not executable */
		}
	}
	else if (pid < 0)
	{
		perror("Fork Error");
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_s = WEXITSTATUS(status);
	}

	return (exit_s);
}
