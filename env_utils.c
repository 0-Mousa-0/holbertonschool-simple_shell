#include "shell.h"

/**
 * _getenv - Get environment variable value
 * @name: Variable name
 * Return: Value or NULL if not found
 */
char *_getenv(const char *name)
{
char **env = environ;
size_t name_len;

if (!name || !env)
return (NULL);

name_len = _strlen(name);

while (*env)
{
if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
return (*env + name_len + 1);
env++;
}

return (NULL);
}

/**
 * _strncmp - Compare first n characters of strings
 * @s1: First string
 * @s2: Second string
 * @n: Number of characters to compare
 * Return: 0 if equal, difference otherwise
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
size_t i;

if (!s1 || !s2)
return (-1);

for (i = 0; i < n; i++)
{
if (s1[i] != s2[i] || s1[i] == '\0')
return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

return (0);
}

/**
 * is_path_command - Check if command contains path separator
 * @command: Command to check
 * Return: 1 if contains '/', 0 otherwise
 */
int is_path_command(const char *command)
{
int i = 0;

if (!command)
return (0);

while (command[i])
{
if (command[i] == '/')
return (1);
i++;
}
return (0);
}

/**
 * build_full_path - Build full path from directory and command
 * @dir: Directory path
 * @command: Command name
 * Return: Full path string or NULL
 */
char *build_full_path(const char *dir, const char *command)
{
char *full_path;
int dir_len, cmd_len;

if (!command)
return (NULL);

cmd_len = _strlen(command);

if (dir == NULL || dir[0] == '\0')
{
full_path = malloc(cmd_len + 1);
if (!full_path)
return (NULL);
_strcpy(full_path, command);
return (full_path);
}

dir_len = _strlen(dir);
full_path = malloc(dir_len + cmd_len + 2);
if (!full_path)
return (NULL);

_strcpy(full_path, dir);
if (dir_len > 0 && dir[dir_len - 1] != '/')
_strcat(full_path, "/");
_strcat(full_path, command);

return (full_path);
}
