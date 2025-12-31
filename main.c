#include "shell.h"

/**
 * main - Entry point for the simple shell
 * * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	char *full_path;

	while (1)
	{
		/* Print prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ":) ", 3);

		nread = getline(&line, &len, stdin);
		if (nread == -1) /* Handle EOF (Ctrl+D) */
		{
			free(line);
			exit(0);
		}

		/* Remove newline character from getline */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		args = tokenize(line);
		/* If line was empty or only spaces, tokenize returns NULL or args[0] is NULL */
		if (args && args[0])
		{
			full_path = find_path(args[0]);

			if (full_path != NULL)
			{
				/* Case: Command found OR is a valid path. OK to fork. */
				execute(args, full_path);

				/* Only free full_path if it was allocated by find_path */
				if (full_path != args[0])
					free(full_path);
			}
			else
			{
				/* CASE: Command not found. No fork is called. */
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			}
		}
		free(args);
	}
	free(line);
	return (0);
}
