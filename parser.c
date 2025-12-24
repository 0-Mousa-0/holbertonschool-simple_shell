#include "shell.h"

/**
 * tokenize_input - Tokenizes input string into arguments
 * @input: Input string
 * Return: Array of arguments or NULL
 */
char **tokenize_input(char *input)
{
    char **args = NULL;
    char *token;
    int i = 0, count = 0;
    char *input_copy;
    
    if (input == NULL || input[0] == '\0')
        return (NULL);
    
    input_copy = _strdup(input);
    if (input_copy == NULL)
        return (NULL);
    
    /* Count tokens */
    token = strtok(input_copy, " \t");
    while (token != NULL)
    {
        count++;
        token = strtok(NULL, " \t");
    }
    
    free(input_copy);
    
    /* Allocate memory for args */
    args = malloc(sizeof(char *) * (count + 1));
    if (args == NULL)
        return (NULL);
    
    /* Tokenize again to store tokens */
    input_copy = _strdup(input);
    token = strtok(input_copy, " \t");
    
    while (token != NULL)
    {
        args[i] = _strdup(token);
        if (args[i] == NULL)
        {
            free(input_copy);
            cleanup_args(args);
            return (NULL);
        }
        i++;
        token = strtok(NULL, " \t");
    }
    
    args[i] = NULL;
    free(input_copy);
    
    return (args);
}

/**
 * cleanup_args - Frees memory allocated for arguments
 * @args: Array of arguments to free
 */
void cleanup_args(char **args)
{
    int i;
    
    if (args == NULL)
        return;
    
    for (i = 0; args[i] != NULL; i++)
        free(args[i]);
    
    free(args);
}
