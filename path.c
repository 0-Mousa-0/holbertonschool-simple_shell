#include "shell.h"

/**
 * find_path - Finds the executable path for a command
 * @command: Command to find (e.g., "ls")
 * Return: Full path (e.g., "/bin/ls") or NULL if not found
 */
char *find_path(char *command)
{
	char *path, *path_cp, *token, *file_path;
	struct stat st;

	if (!command)
		return (NULL);

	/* Case: Command is a direct path (e.g., /bin/ls or ./hbtn_ls) */
	if (strchr(command, '/'))
	{
		if (stat(command, &st) == 0)
			return (_strdup(command));
		return (NULL);
	}

	/* Get PATH variable */
	path = _getenv("PATH");

	/* CASE: PATH is removed, set to empty, or command is empty */
	if (!path || _strlen(path) == 0)
		return (NULL);

	path_cp = _strdup(path);
	token = strtok(path_cp, ":");
	while (token != NULL)
	{
		/* Construct: folder/command */
		file_path = malloc(_strlen(token) + _strlen(command) + 2);
		if (!file_path)
			break;
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
