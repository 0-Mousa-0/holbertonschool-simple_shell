#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of the variable (e.g., "PATH")
 * Return: Value of the variable or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len;

	if (name == NULL || environ == NULL)
		return (NULL);

	len = _strlen((char *)name);
	while (environ[i])
	{
		/* Using a simple loop to compare without needing strncmp from string.h */
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * _strcpy - Copies a string from src to dest
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, char *src)
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
 * @dest: First string, then result
 * @src: Second string to add
 * Return: Pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
