#include "shell.h"

void execute_command(char **argv)
{
	pid_t pid;
	char *cmd;

	cmd = resolve_command(argv[0]);
	if (!cmd)
	{
		write(2, argv[0], strlen(argv[0]));
		write(2, ": not found\n", 12);
		return; /* ❗ لا fork */
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv, environ);
		exit(1);
	}
	else
		wait(NULL);

	free(cmd);
}

