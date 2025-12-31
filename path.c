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
int i;

if (!command || command[0] == '\0')
return (NULL);

/* Check if command contains '/' */
for (i = 0; command[i]; i++)
if (command[i] == '/')
{
if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
return (_strdup(command));
return (NULL);
}

path = getenv("PATH");
if (path == NULL || path[0] == '\0')
return (NULL);

path_copy = _strdup(path);
if (!path_copy)
return (NULL);

dir = strtok(path_copy, ":");
while (dir != NULL)
{
if (dir[0] != '\0')
{
full_path = malloc(_strlen(dir) + _strlen(command) + 2);
if (!full_path)
{
free(path_copy);
return (NULL);
}
_strcpy(full_path, dir);
_strcat(full_path, "/");
_strcat(full_path, command);
if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
free(path_copy);
return (full_path);
}
free(full_path);
}
dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}
