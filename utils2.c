#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of the variable (e.g., "PATH")
 * Return: Value of the variable or NULL if not found/empty
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
		/* Check if variable starts with 'name=' */
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
/* ... _strcpy and _strcat follow here ... */
