#include "shell.h"

/**
 * has_slash - Check if command contains '/'
 * @command: Command to check
 * Return: 1 if contains '/', 0 otherwise
 */
int has_slash(char *command)
{
int i = 0;

while (command[i])
{
if (command[i] == '/')
return (1);
i++;
}
return (0);
}

/**
 * find_in_path - Find command in PATH
 * @command: Command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_in_path(char *command)
{
char *path, *path_copy, *dir, *full_path;
struct stat st;

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
