#include "shell.h"

/**
 * _strlen - Get string length
 * @s: String
 * Return: Length of string
 */
int _strlen(char *s)
{
    int len = 0;
    
    while (s[len])
        len++;
    
    return (len);
}

/**
 * _strdup - Duplicate a string
 * @str: String to duplicate
 * Return: Duplicated string
 */
char *_strdup(char *str)
{
    char *dup;
    int len, i;
    
    if (str == NULL)
        return (NULL);
    
    len = _strlen(str);
    dup = malloc(len + 1);
    
    if (dup == NULL)
        return (NULL);
    
    for (i = 0; i <= len; i++)
        dup[i] = str[i];
    
    return (dup);
}

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if equal, difference otherwise
 */
int _strcmp(char *s1, char *s2)
{
    int i = 0;
    
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    
    return (s1[i] - s2[i]);
}

/**
 * _strcpy - Copy string
 * @dest: Destination
 * @src: Source
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
    int i = 0;
    
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    return (dest);
}

/**
 * _strcat - Concatenate strings
 * @dest: Destination
 * @src: Source
 * Return: Pointer to dest
 */
char *_strcat(char *dest, char *src)
{
    int dest_len = _strlen(dest);
    int i = 0;
    
    while (src[i])
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    
    return (dest);
}
