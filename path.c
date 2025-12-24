#include "shell.h"

static char *build_path(char *dir, char *cmd)
{
	char *full;

	if (!dir || *dir == '\0')
	{
		full = malloc(strlen(cmd) + 3);
		sprintf(full, "./%s", cmd);
	}
	else
	{
		full = malloc(strlen(dir) + strlen(cmd) + 2);
		sprintf(full, "%s/%s", dir, cmd);
	}
	return (full);
}

char *resolve_command(char *cmd)
{
	char *path, *copy, *p, *start;
	char *full;

	if (!cmd || *cmd == '\0')
		return (NULL);

	/* absolute or relative path */
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	copy = strdup(path);
	start = copy;

	while (1)
	{
		p = strchr(start, ':');
		if (p)
			*p = '\0';

		full = build_path(start, cmd);
		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}
		free(full);

		if (!p)
			break;
		start = p + 1;
	}

	free(copy);
	return (NULL);
}
