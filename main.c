#include "shell.h"

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ":) ", 3);

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (line[0] == '\n')
			continue;

		args = split_line(line);
		if (args && args[0])
			execute(args);

		free(args);
	}

	free(line);
	return (0);
}
