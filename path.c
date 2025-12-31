#include "shell.h"

/**
 * find_path - Finds the executable path for a command
 * @command: Command to find
 * Return: Full path or NULL if not found
 */
char *find_path(char *command)
{
	char *path, *path_cp, *token, *file_path;
	struct stat st;

	/* Case: Command is a direct path (e.g., /bin/ls or ./ls or ../ls) */
	if (strchr(command, '/'))
	{
		if (stat(command, &st) == 0)
			return (_strdup(command));
		return (NULL);
	}

	path = _getenv("PATH");
	if (!path || _strlen(path) == 0)
		return (NULL);

	path_cp = _strdup(path);
	token = strtok(path_cp, ":");
	while (token != NULL)
	{
		file_path = malloc(_strlen(token) + _strlen(command) + 2);
		_strcpy(file_path, token);
		_strcat(file_path, "/");
		_strcat(file_path, command);

		if (stat(file_path, &st) == 0)
		{
			free(path_cp);
			return (file_path);
		}
		free(file_path);
		token = strtok(NULL, ":");
	}

	free(path_cp);
	return (NULL);
}
