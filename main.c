#include "shell.h"

/**
 * main - Entry point for the simple shell
 * Return: 0 on success
 */
int main(void)
{
	shell_loop();
	return (0);
}

/**
 * shell_loop - Main shell loop to read and execute commands
 */
void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	char *full_path;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ":) ", 3);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		args = tokenize(line);
		if (args && args[0])
		{
			full_path = find_path(args[0]);
			if (full_path)
			{
				execute(args, full_path);
				if (full_path != args[0])
					free(full_path);
			}
			else
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			}
		}
		free(args);
	}
	free(line);
}
