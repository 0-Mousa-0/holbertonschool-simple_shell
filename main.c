#include "shell.h"

/**
 * main - Simple shell entry point
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 * Return: Exit status
 */
int main(int argc, char **argv, char **env)
{
    char *input = NULL;
    char **args = NULL;
    int status = 1;
    
    (void)argc;
    (void)argv;
    (void)env;
    
    while (status)
    {
        /* Display prompt if in interactive mode */
        if (isatty(STDIN_FILENO))
            display_prompt();
        
        /* Read input */
        input = read_input();
        if (input == NULL)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }
        
        /* Parse input */
        args = parse_input(input);
        if (args == NULL)
        {
            free(input);
            continue;
        }
        
        /* Execute command */
        if (args[0] != NULL)
            status = execute_command(args);
        
        /* Clean up */
        free(input);
        free_args(args);
    }
    
    return (0);
}
