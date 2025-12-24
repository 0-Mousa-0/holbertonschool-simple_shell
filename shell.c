#include "shell.h"

/**
 * split_line - splits input line into arguments
 */
char **split_line(char *line)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = malloc(sizeof(char *) * 64);
	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * find_command - find command in PATH
 */
char *find_command(char *cmd)
{
	char *path, *path_copy, *token, *full;

	if (!cmd || *cmd == '\0')
		return (NULL);

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	token = strtok(path_copy, ":");

	while (token)
	{
		if (*token == '\0')
		{
			full = malloc(strlen(cmd) + 3);
			sprintf(full, "./%s", cmd);
		}
		else
		{
			full = malloc(strlen(token) + strlen(cmd) + 2);
			sprintf(full, "%s/%s", token, cmd);
		}

		if (access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * execute - execute a command
 */
void execute(char **args)
{
	pid_t pid;
	char *cmd;

	cmd = find_command(args[0]);
	if (!cmd)
	{
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return; /*fork */
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);

	free(cmd);
}
