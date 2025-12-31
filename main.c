#include "shell.h"

/**
 * main - Entry point for the simple shell
 * Return: The last exit status
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	char *full_path;
	int last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ":) ", 3);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(last_status); /* Exit with the status of the last command */
		}

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		args = tokenize(line);
		if (args && args[0])
		{
			full_path = find_path(args[0]);
			if (full_path != NULL)
			{
				/* Capture exit status from the executed command */
				last_status = execute(args, full_path);
				if (full_path != args[0])
					free(full_path);
			}
			else
			{
				/* Command not found: Set status to 127 */
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				last_status = 127;
			}
		}
		free(args);
	}
	return (last_status);
}
