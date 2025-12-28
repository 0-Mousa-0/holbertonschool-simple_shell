#include "shell.h"

/**
 * find_in_path - Find command in PATH directories
 * @command: Command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_in_path(char *command)
{
    char *path, *path_copy, *dir, *full_path;
    struct stat st;
    
    /* Check if command contains '/' (absolute or relative path) */
    if (strchr(command, '/') != NULL)
    {
        if (stat(command, &st) == 0)
            return (_strdup(command));
        return (NULL);
    }
    
    /* Get PATH from environment */
    path = getenv("PATH");
    if (path == NULL)
        return (NULL);
    
    path_copy = _strdup(path);
    if (path_copy == NULL)
        return (NULL);
    
    /* Tokenize PATH and search each directory */
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        /* Allocate memory for full path */
        full_path = malloc(_strlen(dir) + _strlen(command) + 2);
        if (full_path == NULL)
        {
            free(path_copy);
            return (NULL);
        }
        
        /* Build full path: dir + "/" + command */
        _strcpy(full_path, dir);
        _strcat(full_path, "/");
        _strcat(full_path, command);
        
        /* Check if file exists and is executable */
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
 * check_command_exists - Check if command exists
 * @command: Command to check
 * Return: 1 if exists, 0 otherwise
 */
int check_command_exists(char *command)
{
    char *path = find_in_path(command);
    
    if (path != NULL)
    {
        free(path);
        return (1);
    }
    
    return (0);
}
