#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

/**
 * trim_spaces - remove leading and trailing spaces/tabs
 * @str: input string
 * Return: trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	*(end + 1) = '\0';
	return (str);
}

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *command;
	char *argv[64];
	int i;

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

		command = trim_spaces(line);
		if (*command == '\0')
			continue;

		/* build argv */
		i = 0;
		argv[i] = strtok(command, " \t");
		while (argv[i] != NULL && i < 63)
		{
			i++;
			argv[i] = strtok(NULL, " \t");
		}
		argv[i] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				fprintf(stderr, "%s: No such file or directory\n", argv[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
