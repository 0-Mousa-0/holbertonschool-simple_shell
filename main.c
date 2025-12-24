#include "shell.h"

/**
 * main - Entry point for the simple shell
 * Return: Always 0
 */
int main(void)
{
    char *input = NULL;
    size_t len = 0;
    ssize_t read;
    char **args;
    int interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
            print_prompt();

        read = getline(&input, &len, stdin);
        
        if (read == -1)
        {
            handle_eof(input);
        }

        /* Remove newline character */
        if (input[read - 1] == '\n')
            input[read - 1] = '\0';

        /* Skip empty lines and lines with only spaces */
        if (input[0] == '\0' || input[0] == ' ' || input[0] == '\t')
            continue;

        /* Handle exit built-in */
        if (_strcmp(input, "exit") == 0)
        {
            free(input);
            exit(0);
        }

        /* Tokenize input */
        args = tokenize_input(input);
        if (args == NULL || args[0] == NULL)
            continue;

        /* Execute command */
        execute_command(args);
        
        /* Clean up */
        cleanup_args(args);
    }

    free(input);
    return (0);
}
