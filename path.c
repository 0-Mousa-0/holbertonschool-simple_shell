#include "shell.h"

/**
 * find_executable - Find executable in PATH or as absolute/relative path
 * @command: Command to find
 * Return: Full path if found and executable, NULL otherwise
 */
char *find_executable(char *command)
{
    struct stat st;
    char *path, *path_copy, *dir, *full_path;
    
    if (!command || command[0] == '\0')
        return (NULL);
    
    /* Check if command is already a path (contains '/') */
    if (is_path_command(command))
    {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return (_strdup(command));
        return (NULL);
    }
    
    /* Get PATH from environment */
    path = _getenv("PATH");
    
    /* Handle empty PATH or PATH not set */
    if (path == NULL || path[0] == '\0')
    {
        /* For empty PATH, only commands with '/' should work */
        return (NULL);
    }
    
    path_copy = _strdup(path);
    if (!path_copy)
        return (NULL);
    
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        /* Skip empty directories in PATH */
        if (dir[0] != '\0')
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
        }
        dir = strtok(NULL, ":");
    }
    
    free(path_copy);
    return (NULL);
}

/**
 * check_command_exists - Check if command exists without forking
 * @command: Command to check
 * Return: 1 if exists, 0 otherwise
 */
int check_command_exists(char *command)
{
    char *path = find_executable(command);
    
    if (path != NULL)
    {
        free(path);
        return (1);
    }
    
    return (0);
}
