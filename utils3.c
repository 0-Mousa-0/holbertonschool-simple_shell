#include "shell.h"

/**
 * is_whitespace - Checks if character is whitespace
 * @c: Character to check
 * Return: 1 if whitespace, 0 otherwise
 */
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * strip_leading_trailing_spaces - Removes leading/trailing spaces
 * @str: String to strip
 */
void strip_leading_trailing_spaces(char *str)
{
    int i, start = 0, end = _strlen(str) - 1;
    
    if (str == NULL)
        return;
    
    while (is_whitespace(str[start]))
        start++;
    
    while (end >= start && is_whitespace(str[end]))
        end--;
    
    for (i = 0; i <= end - start; i++)
        str[i] = str[start + i];
    
    str[i] = '\0';
}

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
