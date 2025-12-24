#include "shell.h"

/**
 * _getenv - Gets an environment variable
 * @name: Name of the environment variable
 * Return: Value of the variable or NULL
 */
char *_getenv(const char *name)
{
    int i, len;
    
    if (name == NULL || environ == NULL)
        return (NULL);
    
    len = _strlen(name);
    
    for (i = 0; environ[i] != NULL; i++)
    {
        if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
            return (environ[i] + len + 1);
    }
    
    return (NULL);
}

/**
 * file_exists - Checks if a file exists and is executable
 * @path: Path to check
 * Return: 1 if exists and executable, 0 otherwise
 */
int file_exists(char *path)
{
    struct stat st;
    
    if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
        return (1);
    
    return (0);
}

/**
 * build_full_path - Builds full path from directory and command
 * @dir: Directory path
 * @command: Command name
 * Return: Full path string or NULL
 */
char *build_full_path(char *dir, char *command)
{
    char *full_path;
    int dir_len, cmd_len;
    
    dir_len = _strlen(dir);
    cmd_len = _strlen(command);
    
    full_path = malloc(dir_len + cmd_len + 2); /* +2 for '/' and null terminator */
    if (full_path == NULL)
        return (NULL);
    
    _strcpy(full_path, dir);
    
    /* Add '/' if not present at end of directory */
    if (dir_len > 0 && full_path[dir_len - 1] != '/')
    {
        full_path[dir_len] = '/';
        full_path[dir_len + 1] = '\0';
        dir_len++;
    }
    
    _strcat(full_path, command);
    
    return (full_path);
}

/**
 * find_in_path - Finds command in PATH directories
 * @command: Command to find
 * Return: Full path to command or NULL
 */
char *find_in_path(char *command)
{
    char *path, *path_copy, *dir, *full_path;
    
    /* If command contains '/', check directly (absolute or relative path) */
    if (_strchr(command, '/') != NULL)
    {
        if (file_exists(command))
            return (_strdup(command));
        return (NULL);
    }
    
    /* Get PATH environment variable */
    path = _getenv("PATH");
    if (path == NULL || path[0] == '\0')
        return (NULL);
    
    path_copy = _strdup(path);
    if (path_copy == NULL)
        return (NULL);
    
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        full_path = build_full_path(dir, command);
        if (full_path != NULL)
        {
            if (file_exists(full_path))
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
