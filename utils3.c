#include "shell.h"

/**
 * Additional utility functions can be placed here
 * if you need to split functions across more files
 * to maintain the 5-functions-per-file limit
 */

/**
 * Example: Help built-in
 * @args: Arguments
 * Return: 1
 */
int print_help(char **args)
{
    (void)args;
    
    printf("Simple Shell\n");
    printf("Built-in commands: cd, env, exit, help\n");
    printf("External commands are searched in PATH\n");
    
    return (1);
}
