#include "shell.h"

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
 * print_help - Print help information
 * @args: Arguments
 * Return: 1
 */
int print_help(char **args)
{
    (void)args;
    
    printf("Simple Shell Help\n");
    printf("Usage: command [arguments]\n");
    printf("Built-in commands: cd, env, exit, help\n");
    printf("External commands are searched in PATH\n");
    
    return (1);
}
