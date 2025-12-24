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
            handle_eof(input);

        if (read > 0 && input[read - 1] == '\n')
            input[read - 1] = '\0';

        remove_comments(input);
        strip_leading_trailing_spaces(input);

        if (input[0] == '\0')
            continue;

        args = tokenize_input(input);
        if (args == NULL || args[0] == NULL)
        {
            if (args)
                cleanup_args(args);
            continue;
        }

        execute_command(args);
        cleanup_args(args);
    }

    free(input);
    return (0);
}
