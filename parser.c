#include "shell.h"

int is_empty_line(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char **parse_line(char *line)
{
	char **argv;
	int i = 0;
	char *tok;

	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	tok = strtok(line, " \t\n");
	while (tok)
	{
		argv[i++] = tok;
		tok = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;
	return (argv);
}
