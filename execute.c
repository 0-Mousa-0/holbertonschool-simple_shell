#include "shell.h"

/**
 * execute - Forks a process and executes the command
 * @args: Command and arguments
 * @path: The resolved path to the executable
 * Return: 1 on success
 */
int execute(char **args, char *path)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(path, args, environ) == -1)
		{
			perror("Error");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Fork Error");
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, WUNTRACED);
	}

	return (1);
}
