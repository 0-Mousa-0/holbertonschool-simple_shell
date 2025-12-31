#include "shell.h"

int _strlen(char *s)
{
int len = 0;

if (!s)
return (0);

while (s[len])
len++;

return (len);
}

char *_strdup(char *str)
{
char *dup;
int len, i;

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

int _strcmp(char *s1, char *s2)
{
int i = 0;

while (s1[i] && s2[i] && s1[i] == s2[i])
i++;

return (s1[i] - s2[i]);
}

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
