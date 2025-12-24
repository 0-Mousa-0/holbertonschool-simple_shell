#include "shell.h"

/**
 * file_exists - Checks if a file exists and is executable
 * @path: Path to check
 * Return: 1 if exists and executable, 0 otherwise
 */
int file_exists(char *path)
{
    struct stat st;
    
    if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
    {
        if (access(path, X_OK) == 0)
            return (1);
    }
    
    return (0);
}

/**
 * is_absolute_path - Checks if command is an absolute or relative path
 * @command: Command to check
 * Return: 1 if absolute/relative path, 0 if just a command name
 */
int is_absolute_path(char *command)
{
    if (command == NULL)
        return (0);
    
    return (command[0] == '/' || 
           (command[0] == '.' && command[1] == '/') ||
           (command[0] == '.' && command[1] == '.' && command[2] == '/'));
}

/**
 * build_full_path - Builds full path from directory and command
 * @dir: Directory path
 * @command: Command name
 * Return: Full path string or NULL
 */
static char *build_full_path(char *dir, char *command)
{
    char *full_path;
    int dir_len, cmd_len;
    
    dir_len = _strlen(dir);
    cmd_len = _strlen(command);
    
    full_path = malloc(dir_len + cmd_len + 2);
    if (full_path == NULL)
        return (NULL);
    
    _strcpy(full_path, dir);
    
    if (dir_len > 0 && full_path[dir_len - 1] != '/')
    {
        _strcat(full_path, "/");
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
    
    if (command == NULL || command[0] == '\0')
        return (NULL);
    
    if (is_absolute_path(command))
    {
        if (file_exists(command))
            return (_strdup(command));
        return (NULL);
    }
    
    path = _getenv("PATH");
    if (path == NULL || path[0] == '\0')
        return (NULL);
    
    path_copy = _strdup(path);
    if (path_copy == NULL)
        return (NULL);
    
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        if (dir[0] != '\0')
        {
            full_path = build_full_path(dir, command);
            if (full_path && file_exists(full_path))
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
