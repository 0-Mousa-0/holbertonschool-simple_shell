#include "shell.h"

/**
 * find_executable - Find executable in PATH
 * @command: Command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_executable(char *command)
{
struct stat st;
char *path, *path_copy, *dir, *full_path;

if (!command || command[0] == '\0')
return (NULL);

if (is_path_command(command))
{
if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
return (_strdup(command));
return (NULL);
}

path = _getenv("PATH");

/* If PATH is NULL (not set), command not found */
if (path == NULL)
return (NULL);

/* If PATH is empty string, command not found */
if (path[0] == '\0')
return (NULL);

path_copy = _strdup(path);
if (!path_copy)
return (NULL);

dir = strtok(path_copy, ":");
while (dir != NULL)
{
full_path = build_full_path(dir, command);
if (!full_path)
{
free(path_copy);
return (NULL);
}

if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
free(path_copy);
return (full_path);
}

free(full_path);
dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}
