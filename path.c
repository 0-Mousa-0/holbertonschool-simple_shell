#include "shell.h"

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
    
    if (!dir || !command)
        return (NULL);
    
    dir_len = _strlen(dir);
    cmd_len = _strlen(command);
    
    full_path = malloc(dir_len + cmd_len + 2);
    if (!full_path)
        return (NULL);
    
    _strcpy(full_path, dir);
    if (dir[dir_len - 1] != '/')
        _strcat(full_path, "/");
    _strcat(full_path, command);
    
    return (full_path);
}

/**
 * find_executable - Find executable in PATH or as absolute/relative path
 * @command: Command to find
 * Return: Full path if found and executable, NULL otherwise
 */
char *find_executable(char *command)
{
    struct stat st;
    char *path, *path_copy, *dir, *full_path;
    
    if (!command)
        return (NULL);
    
    /* Check if command is already a path */
    if (is_path_command(command))
    {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return (_strdup(command));
        return (NULL);
    }
    
    /* Get PATH from environment */
    path = _getenv("PATH");
    if (path == NULL || path[0] == '\0')
    {
        return (NULL);
    }
    
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

/**
 * find_in_path - Legacy function for compatibility
 * @command: Command to find
 * Return: Full path if found
 */
char *find_in_path(char *command)
{
    return (find_executable(command));
}
