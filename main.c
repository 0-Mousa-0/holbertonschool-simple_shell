#include "shell.h"

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t r;
	char **argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, ":) ", 3);

		r = getline(&line, &len, stdin);
		if (r == -1)
			break;

		if (is_empty_line(line))
			continue;

		argv = parse_line(line);
		if (!argv || !argv[0])
		{
			free(argv);
			continue;
		}

		execute_command(argv);
		free(argv);
	}

	free(line);
	return (0);
}
