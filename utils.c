#include "shell.h"

int _strlen(char *s)
{
	int i = 0;
	while (s[i]) i++;
	return (i);
}

char *_strdup(char *str)
{
	char *new;
	int i;

	if (str == NULL) return (NULL);
	new = malloc(_strlen(str) + 1);
	if (!new) return (NULL);
	for (i = 0; str[i]; i++) new[i] = str[i];
	new[i] = '\0';
	return (new);
}

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
