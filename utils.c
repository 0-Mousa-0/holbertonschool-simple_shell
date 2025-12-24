#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: The string to measure
 * Return: Length of the string
 */
int _strlen(const char *s)
{
    int len = 0;
    
    if (s == NULL)
        return (0);
        
    while (s[len] != '\0')
        len++;
    
    return (len);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *str)
{
    char *dup;
    int i, len;
    
    if (str == NULL)
        return (NULL);
    
    len = _strlen(str);
    dup = malloc(sizeof(char) * (len + 1));
    
    if (dup == NULL)
        return (NULL);
    
    for (i = 0; i <= len; i++)
        dup[i] = str[i];
    
    return (dup);
}

/**
 * _strcpy - Copies a string
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
    int i = 0;
    
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    return (dest);
}

/**
 * _strcat - Concatenates two strings
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to dest
 */
char *_strcat(char *dest, const char *src)
{
    int dest_len = _strlen(dest);
    int i;
    
    for (i = 0; src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];
    
    dest[dest_len + i] = '\0';
    
    return (dest);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if equal, negative if s1 < s2, positive if s1 > s2
 */
int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
