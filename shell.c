#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *argv[2];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			free(line);
			exit(0);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (*line == '\0')
			continue;

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;

			if (execve(line, argv, environ) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}
}
