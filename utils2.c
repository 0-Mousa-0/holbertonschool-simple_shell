#include "shell.h"

/**
 * _strlen - Calculate length of string
 * @s: String
 * Return: Length
 */
int _strlen(char *s)
{
int len = 0;

while (s && s[len])
len++;

return (len);
}

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 * Return: Difference
 */
int _strcmp(char *s1, char *s2)
{
while (*s1 && (*s1 == *s2))
{
s1++;
s2++;
}

return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strdup - Duplicate a string
 * @str: String to duplicate
 * Return: Duplicated string
 */
char *_strdup(char *str)
{
char *dup;
int i, len;

if (!str)
return (NULL);

len = _strlen(str);
dup = malloc(len + 1);

if (!dup)
return (NULL);

for (i = 0; i <= len; i++)
dup[i] = str[i];

return (dup);
}
