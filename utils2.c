#include "shell.h"

/**
 * _strchr - Locates character in string
 * @s: String to search
 * @c: Character to find
 * Return: Pointer to first occurrence or NULL
 */
char *_strchr(const char *s, char c)
{
    while (*s != '\0')
    {
        if (*s == c)
            return (char *)s;
        s++;
    }
    
    return (NULL);
}

/**
 * _strncmp - Compares two strings up to n characters
 * @s1: First string
 * @s2: Second string
 * @n: Number of characters to compare
 * Return: 0 if equal, negative if s1 < s2, positive if s1 > s2
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    
    for (i = 0; i < n; i++)
    {
        if (s1[i] != s2[i])
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        if (s1[i] == '\0')
            break;
    }
    
    return 0;
}

/**
 * print_prompt - Prints the shell prompt
 */
void print_prompt(void)
{
    write(STDOUT_FILENO, ":) ", 3);
}

/**
 * handle_eof - Handles end of file (Ctrl+D)
 * @input: Input string to free
 */
void handle_eof(char *input)
{
    free(input);
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "\n", 1);
    exit(0);
}

/**
 * remove_comments - Removes comments from input
 * @input: Input string
 */
void remove_comments(char *input)
{
    int i;
    
    for (i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '#')
        {
            if (i == 0 || input[i - 1] == ' ' || input[i - 1] == '\t')
            {
                input[i] = '\0';
                break;
            }
        }
    }
}
