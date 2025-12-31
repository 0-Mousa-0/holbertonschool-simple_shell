#include "shell.h"

/**
 * find_command - Find the full path of a command
 * @command: The command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_command(char *command)
{
char *path, *path_copy, *dir, *full_path;
struct stat st;

if (!command || command[0] == '\0')
return (NULL);

if (strchr(command, '/'))
{
if (stat(command, &st) == 0)
{
if (st.st_mode & S_IXUSR || access(command, X_OK) == 0)
return (strdup(command));
}
return (NULL);
}

path = getenv("PATH");
if (!path || path[0] == '\0')
return (NULL);

path_copy = strdup(path);
if (!path_copy)
return (NULL);

dir = strtok(path_copy, ":");
while (dir)
{
full_path = malloc(strlen(dir) + strlen(command) + 2);
if (!full_path)
{
free(path_copy);
return (NULL);
}

sprintf(full_path, "%s/%s", dir, command);

if (stat(full_path, &st) == 0)
{
if (st.st_mode & S_IXUSR || access(full_path, X_OK) == 0)
{
free(path_copy);
return (full_path);
}
}

free(full_path);
dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}

/**
 * is_builtin - Check if a command is built-in
 * @command: Command to check
 * Return: 1 if built-in, 0 otherwise
 */
int is_builtin(char *command)
{
if (!command)
return (0);

if (strcmp(command, "exit") == 0 ||
strcmp(command, "env") == 0)
return (1);

return (0);
}

/**
 * handle_builtin - Handle built-in commands
 * @args: Command arguments
 * Return: Status code
 */
int handle_builtin(char **args)
{
if (strcmp(args[0], "exit") == 0)
return (shell_exit(args));
else if (strcmp(args[0], "env") == 0)
return (shell_env(args));

return (1);
}

/**
 * shell_exit - Exit the shell
 * @args: Arguments
 * Return: Always 0
 */
int shell_exit(char **args)
{
(void)args;
exit(0);
}

/**
 * shell_env - Print environment variables
 * @args: Arguments
 * Return: Always 0
 */
int shell_env(char **args)
{
int i = 0;
(void)args;

while (environ[i])
{
write(STDOUT_FILENO, environ[i], strlen(environ[i]));
write(STDOUT_FILENO, "\n", 1);
i++;
}

return (0);
}
